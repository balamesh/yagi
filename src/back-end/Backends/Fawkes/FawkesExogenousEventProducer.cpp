
/***************************************************************************
 *  FawkesExogenousEventProducer.cpp - Fawkes exogenous event producer
 *
 *  Created: Tue Feb 24 11:21:52 2015
 *  Copyright  2015  Tim Niemueller [www.niemueller.de]
 ****************************************************************************/

/* Redistribution and use in source and binary forms, with or without
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

#include "FawkesExogenousEventProducer.h"
#include "yagi_protobuf.h"

// Fawkes includes
#include <logging/logger.h>
#include <utils/misc/string_split.h>

// See comment in getEvent() why these are necessary
#include <llsf_msgs/ExplorationInfo.pb.h>

namespace yagi {
namespace execution {
#if 0 /* just to make Emacs auto-indent happy */
}}
#endif

FawkesExogenousEventProducer::FawkesExogenousEventProducer(std::shared_ptr<fawkes::Logger> logger,
							   std::shared_ptr<yagi_protobuf::YAGIProtobuf> pb)
  : logger_(logger), pb_(pb)
{
  exp_info_processed_ = false;
}

FawkesExogenousEventProducer::~FawkesExogenousEventProducer()
{
}


bool
FawkesExogenousEventProducer::eventAvailable()
{
  return pb_->yagi_pb_events_pending();
}

std::vector<std::pair<std::string, std::unordered_map<std::string, std::string>>>
FawkesExogenousEventProducer::getEvent()
{
  std::vector<std::pair<std::string, std::unordered_map<std::string, std::string>>> events;

  std::list<yagi_protobuf::YAGIProtobuf::MessageData> messages =
    pb_->yagi_pb_process();

  /* This would be the nice version, but due to YAGI's currently limited
     capabilities regarding fluent assignments (only pre-defined domains,
     no numerics, no conditional assignments, no structures, no lists)
     having a generic event is unfortunately not very useful

  for (const yagi_protobuf::YAGIProtobuf::MessageData &m : messages) {
    std::unordered_map<std::string, std::string> variables;
    variables["$endpoint_host"] = m.endpoint_host;
    variables["$endpoint_port"] = std::to_string(m.endpoint_port);
    variables["$component_id"]  = std::to_string(m.comp_id);
    variables["$msg_type"]      = std::to_string(m.msg_type);
    variables["$ptr"]           = pb_->build_pointer(new std::shared_ptr<google::protobuf::Message>(m.msg));
    variables["$client_type"]   =
      (m.ct == yagi_protobuf::YAGIProtobuf::CT_SERVER)
      ? "SERVER"
      : ((m.ct == yagi_protobuf::YAGIProtobuf::CT_CLIENT) ? "CLIENT" : "PEER");
    variables["client_id"]     = std::to_string(m.client_id);
    events.push_back(std::make_pair("protobuf_msg", variables));
  }
  */

  logger_->log_info("FawkesExo", "Processed? %s", exp_info_processed_ ? "YES" : "NO");
  for (const yagi_protobuf::YAGIProtobuf::MessageData &m : messages) {
    logger_->log_debug("FawkesExo", "Processing message of type %s", m.msg->GetTypeName().c_str());

    std::shared_ptr<llsf_msgs::ExplorationInfo> expi =
      std::dynamic_pointer_cast<llsf_msgs::ExplorationInfo>(m.msg);
    if (expi && ! exp_info_processed_) {
      exp_info_processed_ = true;
      for (int i = 0; i < expi->machines_size(); ++i) {
	const llsf_msgs::ExplorationMachine &machine = expi->machines(i);
	if (machine.team_color() == llsf_msgs::CYAN) {
	  // It is an exploration info message
	  std::unordered_map<std::string, std::string> variables;
	  variables["$machine"] = machine.name();
	  events.push_back(std::make_pair("exploration_machine", variables));
	}
      }

      for (int i = 0; i < expi->signals_size(); ++i) {
	const llsf_msgs::ExplorationSignal &exp_signal = expi->signals(i);
	std::unordered_map<std::string, std::string> variables;
	variables["$type"] = exp_signal.type();
	variables["$red"]  = llsf_msgs::LightState_Name(exp_signal.lights(0).state());
	variables["$yellow"]  = llsf_msgs::LightState_Name(exp_signal.lights(1).state());
	variables["$green"]  = llsf_msgs::LightState_Name(exp_signal.lights(2).state());
	events.push_back(std::make_pair("exploration_type", variables));
      }
    }
  }

  logger_->log_info("FawkesExo", "Returning %zu events", events.size());

  return events;
}

} /* namespace execution */
} /* namespace yagi */
