#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>      

using namespace std;

struct c_unique {
  int current;
  c_unique() {current=0;}
  int operator()() {return ++current;}
} UniqueNumber;

//param1: nr of floors.
//param2: nr of on
//param3: filename
int main (int argc, char* argv[]) {

  int nrOfFloors = atoi(argv[1]);
  int nrOfOn = atoi(argv[2]);
  std::string fname(argv[3]);
  //std::string gologProcToExec(argv[4]);
  
  
  std::vector<int> possibleOnValues (nrOfFloors);
  std::generate (possibleOnValues.begin(), possibleOnValues.end(), UniqueNumber);
  
  std::vector<int> possibleInitialCurrFloorValues (nrOfFloors);
  std::generate (possibleInitialCurrFloorValues.begin(), possibleInitialCurrFloorValues.end(), UniqueNumber);
  
  ofstream yagiFile;
  ofstream gologFile;
  yagiFile.open(std::string{fname + ".y"});
  gologFile.open(std::string{fname + ".pl"});
  
  yagiFile << "fact floors[{";
  for (int i=0; i<nrOfFloors; i++)
  {
    yagiFile << "\"" << i << "\"" << ",";
  }
  yagiFile << "\"" << nrOfFloors << "\"" << "}];\n";
  
  yagiFile << "floors = {";
  for (int i=0; i<nrOfFloors; i++)
  {
    yagiFile << "<" << "\"" << i << "\"" << ">,";
  }
  yagiFile << "<" << "\"" << nrOfFloors << "\"" << ">};\n"; 
  
  yagiFile << "fluent fon[{";
  for (int i=1; i<nrOfFloors; i++)
  {
    yagiFile << "\"" << i << "\"" << ",";
  }
  yagiFile << "\"" << nrOfFloors << "\"" << "}];\n";
 
  
  std::mt19937 rng;
  auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  rng.seed(seed);
  
  
  yagiFile << "fon = {";
  for (int i=1; i<nrOfOn; i++)
  {
    std::uniform_int_distribution<uint32_t> uniformDist(0, possibleOnValues.size()-1);
    auto onValIdx = uniformDist(rng);
    yagiFile << "<" << "\"" << possibleOnValues[onValIdx] << "\"" << ">,";
    gologFile << "on(" << possibleOnValues[onValIdx] << ",s0).\n";
    
    possibleOnValues.erase(std::begin(possibleOnValues) + onValIdx);
  }

  std::uniform_int_distribution<uint32_t> uniformDist(0, possibleOnValues.size()-1);
  auto onValIdx = uniformDist(rng);
  yagiFile << "<" << "\"" << possibleOnValues[onValIdx] << "\"" << ">};\n"; 
  gologFile << "on(" << possibleOnValues[onValIdx] << ",s0).\n";
  
  yagiFile << "fluent currFloor[{";
  for (int i=0; i<nrOfFloors; i++)
  {
    yagiFile << "\"" << i << "\"" << ",";
  }
  yagiFile << "\"" << nrOfFloors << "\"" << "}];\n";
  
  yagiFile << "currFloor = {";
  
  std::uniform_int_distribution<uint32_t> uniformDistCurrFloor(0, possibleInitialCurrFloorValues.size()-1);
  auto currFloorValIdx = uniformDistCurrFloor(rng);
  yagiFile << "<" << "\"" << possibleInitialCurrFloorValues[currFloorValIdx] << "\"" << ">};\n"; 
  gologFile << "currentFloor(" << possibleInitialCurrFloorValues[currFloorValIdx] << ",s0).\n";
  
  //gologFile << ":-include('" << gologProcToExec << "')." << std::endl;
  
  yagiFile.close();
  gologFile.close();
  return 0;
}