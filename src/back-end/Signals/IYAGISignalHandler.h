/**
 * @file   IYAGISignalHandler.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Basic functionality of a YAGI signal handler
 */

#ifndef IYAGISIGNALHANDLER_H_
#define IYAGISIGNALHANDLER_H_

#include <string>
#include <unordered_map>
#include <vector>

namespace yagi {
namespace execution {

/**
 * Abstract class for basic functionality of a YAGI signal handler
 */
class IYAGISignalHandler
{
  protected:
    /**
     * True if it is searched over
     */
    bool isSearch_ = false;

  public:
    /**
     * Default ctor
     */
    IYAGISignalHandler();

    /**
     * Default dtor
     */
    virtual ~IYAGISignalHandler();

    /**
     * Executes a YAGI signal command
     * @param content The data to signal
     * @param variables Potential variables that get set via the signal of a setting action
     * @return The variables and the values that got set from a setting action
     */
    virtual std::unordered_map<std::string, std::string> signal(const std::string& content,
        const std::vector<std::string>& variables) = 0;

    /**
     * Setter for isSearch flag
     * @param isSearch True if it's search, false otherwise
     */
    void setIsSearch(bool isSearch)
    {
      isSearch_ = isSearch;
    }
};

} /* namespace execution */
} /* namespace yagi */

#endif /* IYAGISIGNALHANDLER_H_ */
