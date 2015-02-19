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

namespace yagi {
namespace execution {
#if 0 /* just to make Emacs auto-indent happy */
}}
#endif

FawkesSignalHandler::FawkesSignalHandler()
{
}

FawkesSignalHandler::~FawkesSignalHandler()
{
}

std::unordered_map<std::string, std::string>
FawkesSignalHandler::signal(const std::string &content, const std::vector<std::string> &variables)
{
  /*
  //no variables passed => no setting actions, just print whatever
  //there is to print
  if (!variables.size())
  {
    {
      std::lock_guard<std::mutex> lk(signalMutex);
      std::cout << ">>>> " << (!isSearch_ ? "[Signal] " : "[Search] [Signal] ") << content
          << std::endl;

    }
    return std::unordered_map<std::string, std::string> { };
  }
  else //print and wait for input
  {
    std::unordered_map<std::string, std::string> retVals { };
    std::cout << ">>>> "
        << (!isSearch_ ? "[Setting Action Signal] " : "[Search] [Setting Action Signal] ")
        << content << std::endl;

    char* buffer = nullptr;

    for (const auto& var : variables)
    {
      buffer = readline((">>>> Enter string-value for variable " + var + ": ").c_str());
      retVals[var] = buffer;
    }
  }
  */

  std::unordered_map<std::string, std::string> rv;
  return rv;
}

} /* namespace execution */
} /* namespace yagi */
