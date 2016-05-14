
/***************************************************************************
 *  FawkesBackend.h - Fawkes backend for YAGI
 *
 *  Created: Thu Feb 19 17:45:31 2015
 *  Copyright  2015  Tim Niemueller [www.niemueller.de]
 *             2016  Nicolas Limpert
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

#ifndef FAWKESBACKEND_H
#define FAWKESBACKEND_H

#include "../../Backend.h"

namespace fawkes {
  class Logger;
}
namespace yagi_protobuf {
  class YAGIProtobuf;
}

namespace yagi {
namespace execution {
#if 0 /* just to make Emacs auto-indent happy */
}}
#endif

class FawkesSignalHandler;
class FawkesExogenousEventProducer;

class FawkesBackend: public Backend
{
 protected:
  void creatSignalHandler() override;
  void createExogenousEventProducer() override;

 public:
  FawkesBackend();

 private:
  std::shared_ptr<FawkesSignalHandler>          fawkes_signal_handler_;
  std::shared_ptr<FawkesExogenousEventProducer> fawkes_exo_prod_;
  // YAGI cannot hold arbitrary strings in fluents or facts.
  // We have to keep the types of machines according to LightSpec here.
  std::unordered_map<std::string, std::string >* lightspecs_to_types_;


  std::shared_ptr<fawkes::Logger>               logger_;
  std::shared_ptr<yagi_protobuf::YAGIProtobuf>  pb_;
};


PLUMA_INHERIT_PROVIDER(FawkesBackend, Backend)

} /* namespace execution */
} /* namespace yagi */

#endif // FAWKESBACKEND_H
