/***************************************************************************
 *  FawkesSignalHandler.cpp - Fawkes Signal Handler
 *
 *  Created: Thu Feb 19 17:46:33 2015
 *  Copyright  2015  Tim Niemueller [www.niemueller.de]
 ****************************************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "FawkesSignalHandler.h"

// Fawkes includes
#include <blackboard/remote.h>
#include <logging/console.h>
#include <interfaces/SkillerInterface.h>
#include <utils/time/time.h>

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdio>

using namespace fawkes;

namespace yagi {
namespace execution {
#if 0 /* just to make Emacs auto-indent happy */
}}
#endif

FawkesSignalHandler::FawkesSignalHandler()
{
  logger_ = std::make_shared<ConsoleLogger>();
}

FawkesSignalHandler::~FawkesSignalHandler()
{
  if (interfaces_.find("SkillerInterface::Skiller") == interfaces_.end()) {
    SkillerInterface *skiller_if =
      dynamic_cast<SkillerInterface *>(interfaces_["SkillerInterface::Skiller"]);
    if (skiller_if && skiller_if->has_writer() &&
	(skiller_if->exclusive_controller() == skiller_if->serial()))
    {
      logger_->log_info("[Fawkes]", "Releasing exclusive skiller control");
      skiller_if->msgq_enqueue(new SkillerInterface::ReleaseControlMessage());
    }
  }

  if (blackboard_) {
    for (auto iface : interfaces_) {
      blackboard_->close(iface.second);
    }
  }
}

std::unordered_map<std::string, std::string>
FawkesSignalHandler::signal(const std::string &content, const std::vector<std::string> &variables)
{
  std::string name_s = isSearch_ ? "[Search|Fawkes]" : "[Fawkes]";
  const char *name = name_s.c_str();

  std::istringstream iss(content);
  std::vector<std::string> params;
  std::copy(std::istream_iterator<std::string>(iss),
	    std::istream_iterator<std::string>(),
	    std::back_inserter(params));
  if (params.empty()) {
    logger_->log_error(name, "Called without useful content: '%s'", content.c_str());
    return {};
  }
  std::string &cmd = params.front();

  std::lock_guard<std::mutex> lock(signal_mutex_);
  logger_->log_debug(name, "received: %s", content.c_str());

  //no variables passed => no setting actions
  if (variables.empty()) {
    if (cmd == "bb-connect") {
      if (blackboard_) {
	logger_->log_warn(name, "Already connected to blackboard");
	return {};
      }

      std::string  host = "localhost";
      unsigned int port = 1910;
      if (params.size() > 1)  host = params[1];
      if (params.size() > 2)  port = std::stoul(params[2]);
      if (port > 65535) {
	logger_->log_error(name, "Invalid port %u (> 65535)", port);
	return {};
      }
      logger_->log_info(name, "Connecting to remote blackboard %s:%u", host.c_str(), port);
      try {
	blackboard_ = std::make_shared<RemoteBlackBoard>(host.c_str(), port);
      } catch (Exception &e) {
	logger_->log_error(name, "Failed to connect to blackboard: %s", e.what_no_backtrace());
      }


    } else if (cmd == "bb-disconnect") {
      if (blackboard_) {
	for (auto iface : interfaces_) {
	  blackboard_->close(iface.second);
	}
	interfaces_.clear();
      }
      blackboard_.reset();
    } else if (cmd == "bb-open") {
      if (! blackboard_) {
	logger_->log_error(name, "Blackboard is not connected, cannot open interfaces");
	return {};
      }
      if (params.size() != 4) {
	logger_->log_error(name, "bb-open usage: bb-open <READ|WRITE> <type> <ID>,"
			   "invalid call '%s'", content.c_str());
	return {};
      }
      try {
	Interface *iface;
	if (params[1] == "READ") {
	  iface = blackboard_->open_for_reading(params[2].c_str(), params[3].c_str());
	} else {
	  iface = blackboard_->open_for_writing(params[2].c_str(), params[3].c_str());
	}
	interfaces_[iface->uid()] = iface;
      } catch (Exception &e) {
 	logger_->log_error(name, "Failed to open interface %s::%s (%s): %s",
			   params[2].c_str(), params[3].c_str(), params[1].c_str(),
			   e.what_no_backtrace());
      }
    } else if (cmd == "bb-close") {
      if (! blackboard_) {
	logger_->log_error(name, "Blackboard is not connected, cannot open interfaces");
	return {};
      }
      if (params.size() != 2) {
	logger_->log_error(name, "bb-close usage: bb-close <UID>,"
			   "invalid call '%s'", content.c_str());
	return {};
      }

      std::string &uid = params[1];
      if (interfaces_.find(uid) == interfaces_.end()) {
	logger_->log_error(name, "bb-close: interface %s has not been opened", uid.c_str());
	return {};
      }

      blackboard_->close(interfaces_[uid]);
      interfaces_.erase(uid);

    } else if (cmd == "bb-read") {
      if (! blackboard_) {
	logger_->log_error(name, "Blackboard is not connected, cannot read interface");
	return {};
      }
      if (params.size() != 2) {
	logger_->log_error(name, "bb-read usage: bb-read <UID>,"
			   "invalid call '%s'", content.c_str());
	return {};
      }

      std::string &uid = params[1];
      if (interfaces_.find(uid) == interfaces_.end()) {
	logger_->log_error(name, "bb-read: interface %s has not been opened", uid.c_str());
	return {};
      }

      if (interfaces_[uid]->is_writer()) {
	logger_->log_warn(name, "bb-read: interface %s is opened for writing,"
			  " reading makes no sense", uid.c_str());
	return {};
      }

      interfaces_[uid]->read();

    } else if (cmd == "bb-read-all") {
      if (! blackboard_) {
	logger_->log_error(name, "Blackboard is not connected, cannot read interface");
	return {};
      }
      for (auto &i : interfaces_) {
	if (! i.second->is_writer())  i.second->read();
      }

    } else if (cmd == "log") {
      if (params.size() < 3) {
	logger_->log_error(name, "log usage: log <debug|info|warn|error> <msg>+"
			   "invalid call '%s'", content.c_str());
	return {};
      }

      Logger::LogLevel level = Logger::LL_INFO;
      if (params[1] == "debug") {
	level = Logger::LL_DEBUG;
      } else if (params[1] == "info") {
	level = Logger::LL_INFO;
      } else if (params[1] == "warn") {
	level = Logger::LL_WARN;
      } else if (params[1] == "error") {
	level = Logger::LL_ERROR;
      } else {
	logger_->log_warn(name, "Unknown log level '%s', using info", params[1].c_str());
      }

      // 5: after the first space between "log" and the level
      std::string msg = content.substr(content.find(' ', 5));
      logger_->log(level, name, "%s", msg.c_str());

    } else if (cmd.find('{') != std::string::npos) {
      // it's a skill call
      if (interfaces_.find("SkillerInterface::Skiller") == interfaces_.end()) {
	// Interface not opened, do so now
	try {
	  SkillerInterface *sif = blackboard_->open_for_reading<SkillerInterface>("Skiller");
	  interfaces_[sif->uid()] = sif;
	} catch (Exception &e) {
	  logger_->log_error(name, "Failed to open skiller interface: %s",
			     e.what_no_backtrace());
 	  return {};
	}
      }
      SkillerInterface *skiller_if =
	dynamic_cast<SkillerInterface *>(interfaces_["SkillerInterface::Skiller"]);
      if (! skiller_if) {
	logger_->log_error(name, "Failed to cast skiller interface");
	return {};
      }
      if (! skiller_if->has_writer()) {
	logger_->log_error(name, "Skiller interface has no writer, skiller plugin not loaded?");
	return {};
      }

      if ((skiller_if->exclusive_controller() != skiller_if->serial()) && skiller_if->has_writer()) {
	logger_->log_info(name, "Acquiring exclusive skiller control");
	SkillerInterface::AcquireControlMessage *msg =
	  new SkillerInterface::AcquireControlMessage(/* steal control */ true);
	skiller_if->msgq_enqueue(msg);
      }

      SkillerInterface::ExecSkillMessage *exec_msg =
	new SkillerInterface::ExecSkillMessage(content.c_str());
      skiller_if->msgq_enqueue(exec_msg);

    } else {
      logger_->log_warn(name, "Unknown command '%s' received, ignoring", content.c_str());
    }

    return {};
  }
  else //print and wait for input
  {
    if (cmd == "bb-get") {
      if (! blackboard_) {
	logger_->log_error(name, "Blackboard is not connected, cannot read interface");
	return {};
      }
      if (params.size() != 2) {
	logger_->log_error(name, "bb-read usage: bb-read <UID>,"
			   "invalid call '%s'", content.c_str());
	return {};
      }

      std::string &uid = params[1];
      if (interfaces_.find(uid) == interfaces_.end()) {
	logger_->log_error(name, "bb-read: interface %s has not been opened", uid.c_str());
	return {};
      }

      std::unordered_map<std::string, std::string> rv;

      logger_->log_debug(name, "Getting values");

      Interface *iface = interfaces_[uid];
      InterfaceFieldIterator f_end = iface->fields_end();
      for (const std::string &var : variables) {
	logger_->log_debug(name, "  Looking for %s", var.c_str());
	if (var == "$timestamp") {
	  const Time *t = iface->timestamp();
	  // YAGI does not (yet) have a native time type, therefore
	  // just go for a string that preserves the accuracy
	  rv[var] = std::to_string(t->get_sec()) + "." + std::to_string(t->get_usec());
	} else if (var == "$changed") {
	  rv[var] = iface->changed() ? "true" : "false";
	} else if (var == "$hash") {
	  rv[var] = iface->hash_printable();
	} else if (var == "$writer") {
	  rv[var] = iface->writer();
	} else if (var == "$readers") {
	  std::string reader_str;
	  std::list<std::string> readers = iface->readers();
	  std::for_each(readers.begin(), readers.end(),
			[&reader_str](const std::string &reader) {
			  if (! reader_str.empty())  reader_str += ",";
			  reader_str += reader;
			});

	  rv[var] = reader_str;

	} else {
	  // remove leading $ in variable name
	  std::string field_name = var.substr(1);
	  InterfaceFieldIterator f;
	  for (f = iface->fields(); f != f_end; ++f) {
	    if (field_name == f.get_name()) {
	      rv[var] = f.get_value_string();
	      logger_->log_debug(name, "  Found, setting %s=%s",
				 var.c_str(), f.get_value_string());
	    }
	  }
	}

	if (rv.find(var) == rv.end()) {
	  logger_->log_warn(name, "Field '%s' not found in interface %s",
			    var.c_str(), iface->uid());
	  rv[var] = "";
	}
      }

      logger_->log_info(name, "DONE");
      return rv;
    } else {
      logger_->log_warn(name, "Unknown setting action '%s' received, ignoring", content.c_str());
      return {};
    }
  }

}

} /* namespace execution */
} /* namespace yagi */
