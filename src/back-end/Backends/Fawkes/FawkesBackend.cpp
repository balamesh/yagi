/***************************************************************************
 *  FawkesBackend.cpp - Fawkes backend connector
 *
 *  Created: Thu Feb 19 17:46:53 2015
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

#include "FawkesBackend.h"
#include "FawkesSignalHandler.h"
//include "FileExogenousEventProducer.h"

namespace yagi {
namespace execution {
#if 0 /* just to make Emacs auto-indent happy */
}}
#endif
FawkesBackend::FawkesBackend()
{
  std::cout << "FawkesBackend constructed ..." << std::endl;
}

void FawkesBackend::creatSignalHandler()
{
  std::cout << "FawkesBackend signal handler created ..." << std::endl;
  signal_handler_ = std::make_shared<FawkesSignalHandler>();
}

void FawkesBackend::createExogenousEventProducer()
{
  std::cout << "FawkesBackend exogenous events producer created ..." << std::endl;
  //exogenious_event_producer_ = std::make_shared<FileExogenousEventProducer>();
}

} /* namespace execution */
} /* namespace yagi */
