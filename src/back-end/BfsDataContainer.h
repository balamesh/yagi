/**
 * @file   BfsDataContainer.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Stores data generated during the search procedure
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
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

/**
 * Stores data generated during the search procedure
 */
class BfsDataContainer
{
  private:

    /**
     * Pick/Choose choices during search process
     */
    std::vector<int> choices_;

    /**
     * State resulting from the choices made
     */
    std::shared_ptr<database::DatabaseConnectorBase> state_;

  public:

    /**
     * Default ctor
     */
    BfsDataContainer();

    /**
     * Default dtor
     */
    virtual ~BfsDataContainer();

    /**
     * Getter for the choices
     * @return The choices
     */
    const std::vector<int>& getChoices() const
    {
      return choices_;
    }

    /**
     * Adds a choice to the list of choices
     * @param choiceIdx The choice to add
     */
    void addChoice(int choiceIdx)
    {
      choices_.push_back(choiceIdx);
    }

    /**
     * Getter for the state
     * @return The state, i.e. the database
     */
    const std::shared_ptr<database::DatabaseConnectorBase>& getState() const
    {
      return state_;
    }

    /**
     * Setter or the state
     * @param state The state, i.e. a database
     */
    void setState(const std::shared_ptr<database::DatabaseConnectorBase>& state)
    {
      state_ = state;
    }
};

} /* namespace execution */
} /* namespace yagi */

#endif /* BFSDATACONTAINER_H_ */
