/*
 * BfsDataContainer.h
 *
 *  Created on: Nov 26, 2014
 *      Author: cmaier
 */

#ifndef BFSDATACONTAINER_H_
#define BFSDATACONTAINER_H_

#include <memory>
#include <vector>

namespace yagi {
namespace database {
class DatabaseConnectorBase;
} /* namespace database */
} /* namespace yagi */

namespace yagi {
namespace execution {

class BfsDataContainer
{
  private:
    std::vector<int> choices_;
    std::shared_ptr<database::DatabaseConnectorBase> state_;

  public:
    BfsDataContainer();
    virtual ~BfsDataContainer();

    const std::vector<int>& getChoices() const
    {
      return choices_;
    }

    void addChoice(int choiceIdx)
    {
      choices_.push_back(choiceIdx);
    }

    const std::shared_ptr<database::DatabaseConnectorBase>& getState() const
    {
      return state_;
    }

    void setState(const std::shared_ptr<database::DatabaseConnectorBase>& state)
    {
      state_ = state;
    }
};

} /* namespace execution */
} /* namespace yagi */

#endif /* BFSDATACONTAINER_H_ */
