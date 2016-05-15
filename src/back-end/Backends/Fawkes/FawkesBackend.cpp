/***************************************************************************
 *  FawkesBackend.cpp - Fawkes backend connector
 *
 *  Created: Thu Feb 19 17:46:53 2015
 *  Copyright  2015  Tim Niemueller [www.niemueller.de]
 *             2016  Nicolas Limpert
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

#include "FawkesBackend.h"
#include "FawkesSignalHandler.h"
#include "FawkesExogenousEventProducer.h"
#include "yagi_protobuf.h"

// Fawkes includes
#include <logging/console.h>

namespace yagi {
namespace execution {
#if 0 /* just to make Emacs auto-indent happy */
}}
#endif
FawkesBackend::FawkesBackend()
{
  logger_ = std::make_shared<fawkes::ConsoleLogger>();

  std::vector<std::string> proto_paths = { BASEDIR"/src/libs/llsf_msgs" };
  pb_ = std::make_shared<yagi_protobuf::YAGIProtobuf>(proto_paths);

  long int peer_public  = pb_->yagi_pb_peer_create_local("127.0.0.1", 4421, 4411);
  long int peer_private = pb_->yagi_pb_peer_create_local_crypto("127.0.0.1", 4471, 4451,
								"randomkey",
								"aes-128-cbc");  

  pb_->set_peer_name("public", peer_public);
  pb_->set_peer_name("private", peer_private);

  lightspecs_to_types_ = new std::unordered_map<std::string, std::string >();

  logger_->log_info("FawkesBackend", "Initialization complete");
}

void FawkesBackend::creatSignalHandler()
{
  fawkes_signal_handler_ = std::make_shared<FawkesSignalHandler>(logger_, pb_, lightspecs_to_types_);
  signal_handler_ = std::dynamic_pointer_cast<IYAGISignalHandler>(fawkes_signal_handler_);
  if (! fawkes_signal_handler_ || ! signal_handler_) {
    throw std::runtime_error("Could not create FawkesSignalHandler");
  }
  logger_->log_info("FawkesBackend", "Signal handler created");
}

void FawkesBackend::createExogenousEventProducer()
{
  fawkes_exo_prod_ = std::make_shared<FawkesExogenousEventProducer>(logger_, pb_, lightspecs_to_types_);
  exogenious_event_producer_ = std::dynamic_pointer_cast<IExogenousEventProducer>(fawkes_exo_prod_);
  if (! fawkes_exo_prod_ || ! exogenious_event_producer_) {
    throw std::runtime_error("Could not create FawkesExogenousEventProducer");
  }
  logger_->log_info("FawkesBackend", "Exogenous event producer created");
}

} /* namespace execution */
} /* namespace yagi */
