/*
 * IYAGISignalHandler.h
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */

#ifndef IYAGISIGNALHANDLER_H_
#define IYAGISIGNALHANDLER_H_

#include <string>
#include <unordered_map>
#include <vector>

namespace yagi {
namespace execution {

class IYAGISignalHandler
{
  protected:
    bool isSearch_ = false;

  public:
    IYAGISignalHandler();
    virtual ~IYAGISignalHandler();

    virtual std::unordered_map<std::string, std::string> signal(const std::string& content,
        const std::vector<std::string>& variables) = 0;

    void setIsSearch(bool isSearch)
    {
      isSearch_ = isSearch;
    }
};

} /* namespace execution */
} /* namespace yagi */

#endif /* IYAGISIGNALHANDLER_H_ */
