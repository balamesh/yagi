/***************************************************************************
 *  FawkesSignalHandler.h - Fawkes Signal Handler
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

#ifndef FAWKESSIGNALHANDLER_H_
#define FAWKESSIGNALHANDLER_H_

#include "../../Signals/IYAGISignalHandler.h"

#include <thread>
#include <mutex>
#include <memory>
#include <map>

namespace fawkes {
  class BlackBoard;
  class Logger;
  class Interface;
}

namespace yagi_protobuf {
  class YAGIProtobuf;
}

// LLSF Hack
namespace llsf_msgs {
  class MachineReport;
}

namespace yagi {
namespace execution {
#if 0 /* just to make Emacs auto-indent happy */
}}
#endif

class FawkesSignalHandler: public IYAGISignalHandler
{
 public:
  FawkesSignalHandler(std::shared_ptr<fawkes::Logger> logger,
                      std::shared_ptr<yagi_protobuf::YAGIProtobuf> pb,
                      std::unordered_map<std::string, std::string >* lightspecs_to_types);
  virtual ~FawkesSignalHandler();

  std::unordered_map<std::string, std::string>
    signal(const std::string& content,
	   const std::vector<std::string>& variables) override;

 private:
  std::string skill_exec(const std::string &skill_string, bool wait);
  std::unordered_map<std::string, std::string>
    process_bb_cmd(const char *name,
		   const std::string &cmd, const std::vector<std::string> &params,
		   const std::string &content);

  std::unordered_map<std::string, std::string>
    process_pb_cmd(const char *name,
		   const std::string &cmd, const std::vector<std::string> &params,
		   const std::string &content);

 private:
  std::mutex                                   signal_mutex_;
  std::shared_ptr<fawkes::BlackBoard>          blackboard_;
  std::shared_ptr<fawkes::Logger>              logger_;
  std::map<std::string, fawkes::Interface *>   interfaces_;
  std::shared_ptr<yagi_protobuf::YAGIProtobuf> pb_;
  std::shared_ptr<llsf_msgs::MachineReport>    pb_llsf_mr_;
  bool                                         pb_llsf_beacon_thread_quit_;
  std::thread                                  pb_llsf_beacon_thread_;
  std::unordered_map<std::string, std::string >* lightspecs_to_types_;
};

} /* namespace execution */
} /* namespace yagi */

#endif /* FAWKESSIGNALHANDLER_H_ */
