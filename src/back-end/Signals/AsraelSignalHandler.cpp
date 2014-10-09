/*
 * PrintOutSignalReceiver.cpp
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */

#include "AsraelSignalHandler.h"

#include <mutex>
namespace yagi {
namespace execution {

std::mutex signalMutexAsrael;

AsraelSignalHandler::AsraelSignalHandler()
{
    connectSimulator();
}

AsraelSignalHandler::~AsraelSignalHandler()
{
}

std::vector<std::string> AsraelSignalHandler::chopParameters(std::string params)
{
    std::vector<std::string> plist;

    std::size_t found = params.find_first_of(" ");

    while (found!=std::string::npos)
    {
        std::string p = params.substr(0,found);
        std::string p1 = params.substr(found+1);
        plist.push_back(p);
        params = p1;
        found = params.find_first_of(" ");
    }
    plist.push_back(params);
    return plist;
}

int AsraelSignalHandler::connectSimulator(std::string level)
{
    AsrealRemoteCommandResponse response = client.loadLevel(level);
    std::cout << "level loaded " << level << std::endl;
    return response.code_;
}

std::unordered_map<std::string, std::string> AsraelSignalHandler::signal(
    const std::string& content, const std::vector<std::string>& variables)
{
  AsrealRemoteCommandResponse response;
  //no variables passed => no setting actions, just print whatever
  //there is to print
  if (!variables.size())
  {
    std::lock_guard<std::mutex> lk(signalMutexAsrael);

    std::vector<std::string> params = chopParameters(content);

    std::string action_name = params.front();
    params.erase(params.begin());

    //helper action - loading level - needs God
    if (action_name == "LoadLevel")
    {
        response = client.executeCommand("God", action_name, params);
    }
    else
    {
        // primitive action
        response = client.executeCommand("Gargamel", action_name, params);
    }
    if (response.code_==TRUE)
    {
        std::cout << "action " <<  action_name << " executed sucessfully" << std::endl;
    }
    else
    {
        std::cout << "action " <<  action_name << " failed" << std::endl;
    }

    return std::unordered_map<std::string, std::string> { };
  }
  else //print and wait for input
  {
    std::unordered_map<std::string, std::string> retVals { };

    if (variables.size()!=1)
    {
        std::cout << "asrael allows only setting actions that bind one variable!" << std::endl;
        return retVals;
    }

    std::string var = variables.front();

    std::cout << content << std::endl;

    std::vector<std::string> params = chopParameters(content);

    std::string action_name = params.front();
    params.erase(params.begin());


    for(std::vector<std::string>::iterator i=params.begin();i!=params.end();i++)
    {
        std::cout << *i << std::endl;
    }

    response = client.executeCommand("Gargamel", action_name, params);

    if (response.code_==TRUE)
    {
        std::cout << "sending result: " << response.message_ << std::endl;
        retVals[var]="true";
    }
    else if (response.code_==FALSE)
    {
        std::cout << "sensing result: " << response.message_ << std::endl;
        retVals[var]="false";
    }
    else
    {
        std::cout << "error: " << response.message_ << std::endl;
    }

    return retVals;
  }
}

} /* namespace execution */
} /* namespace yagi */
