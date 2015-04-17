/**
 * @file   CoutCinSignalHandler.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Simple signal handler implementation that uses cin/cout.
 */

#ifndef COUTCINSIGNALHANDLER_H_
#define COUTCINSIGNALHANDLER_H_

#include "../../Signals/IYAGISignalHandler.h"
#include <iostream>
#include <readline/readline.h>

namespace yagi {
namespace execution {

/**
 * Responsible for displaying YAGI signals via cout and reading data via cin
 */
class CoutCinSignalHandler: public IYAGISignalHandler
{
  public:
    /**
     * Default ctor
     */
    CoutCinSignalHandler();

    /**
     * Default dtor
     */
    virtual ~CoutCinSignalHandler();

    /**
     * Processes a YAGI signal
     * @param content The signaled content
     * @param variables The involved variables in case of 'setting'
     * @return The 'setting' values in case it was a setting action signal
     */
    std::unordered_map<std::string, std::string> signal(const std::string& content,
        const std::vector<std::string>& variables) override;
};

} /* namespace execution */
} /* namespace yagi */

#endif /* COUTCINSIGNALHANDLER_H_ */
