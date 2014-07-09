/*
 * InterpretationVisitor.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: cmaier
 */

#include "InterpretationVisitor.h"

InterpretationVisitor::InterpretationVisitor() :
    db_{make_unique<SQLiteConnector>("yagiMainDB.sqlite3")}
{
  //db_ = make_unique<SQLiteConnector>("yagiMainDB.sqlite3");
}

InterpretationVisitor::~InterpretationVisitor()
{
  // TODO Auto-generated destructor stub
}

