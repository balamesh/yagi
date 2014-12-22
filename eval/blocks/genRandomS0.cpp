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

//param1: nr of blocks
//param2: nr of stacks
//param3: filename
//param4: control structure only
//param5: is search
int main (int argc, char* argv[]) {

  int nrOfBlocks = atoi(argv[1]);
  int nrOfStacks = atoi(argv[2]);
  std::string fname(argv[3]);
  bool fine = true;
  
do
{  
  std::vector<int> possibleBlocks (nrOfBlocks);
  std::generate (possibleBlocks.begin(), possibleBlocks.end(), UniqueNumber);
  
  UniqueNumber.current = 0;
  
  std::vector<int> allBlocks (nrOfBlocks);
  std::generate (allBlocks.begin(), allBlocks.end(), UniqueNumber);
  
  std::vector<int> clear;
  
  ofstream yagiFile;
  ofstream gologFile;

  std::mt19937 rng;
  auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  rng.seed(seed);
  
  yagiFile.open(std::string{fname + ".y"});
  gologFile.open(std::string{fname + ".pl"});

  
  yagiFile << "fact bblocks[{";
  for (int i=1; i<nrOfBlocks; i++)
  {
    yagiFile << "\"" << i << "\"" << ",";
  }
  yagiFile << "\"" << nrOfBlocks << "\"" << "}];\n";
  
  yagiFile << "bblocks = {";
  for (int i=1; i<nrOfBlocks; i++)
  {
    yagiFile << "<" << "\"" << i << "\"" << ">,";
  }
  yagiFile << "<" << "\"" << nrOfBlocks << "\"" << ">};\n"; 
  
  yagiFile << "fluent onTable[{";
  for (int i=1; i<nrOfBlocks; i++)
  {
    yagiFile << "\"" << i << "\"" << ",";
  }
  yagiFile << "\"" << nrOfBlocks << "\"" << "}];\n";
 
  //there must be as much blocks on table as there are stacks
  yagiFile << "onTable = {";
  for (int i=1; i<nrOfStacks; i++)
  {
    std::uniform_int_distribution<uint32_t> uniformDist(0, possibleBlocks.size()-1);
    auto onValIdx = uniformDist(rng);
    yagiFile << "<" << "\"" << possibleBlocks[onValIdx] << "\"" << ">,";
    gologFile << "ontable(" << possibleBlocks[onValIdx] << ",s0).\n";
     
    clear.push_back(possibleBlocks[onValIdx]);
    possibleBlocks.erase(std::begin(possibleBlocks) + onValIdx);
  }

  std::uniform_int_distribution<uint32_t> uniformDist(0, possibleBlocks.size()-1);
  auto onValIdx = uniformDist(rng);
  yagiFile << "<" << "\"" << possibleBlocks[onValIdx] << "\"" << ">};\n"; 
  gologFile << "ontable(" << possibleBlocks[onValIdx] << ",s0).\n";
   
  clear.push_back(possibleBlocks[onValIdx]);
  possibleBlocks.erase(std::begin(possibleBlocks) + onValIdx);
  
  yagiFile << "fluent bon[{";
  for (int i=1; i<nrOfBlocks; i++)
  {
    yagiFile << "\"" << i << "\"" << ",";
  }
  yagiFile << "\"" << nrOfBlocks << "\"" << "}][{";
  
  for (int i=1; i<nrOfBlocks; i++)
  {
    yagiFile << "\"" << i << "\"" << ",";
  }
  yagiFile << "\"" << nrOfBlocks << "\"" << "}];\n";
  
  yagiFile << "bon = {";

 
  while (possibleBlocks.size() > 1)
  {
    std::uniform_int_distribution<uint32_t> uniformDistBottomBlock(0, clear.size()-1);
    auto botBlockIdx = uniformDistBottomBlock(rng);
    
    std::uniform_int_distribution<uint32_t> topBlockIdxDist(0, possibleBlocks.size()-1);
    auto topBlockIdx = topBlockIdxDist(rng);

    yagiFile << "<" << "\"" << possibleBlocks[topBlockIdx] << "\",\"" << clear[botBlockIdx] << "\"" << ">,"; 
    gologFile << "on(" << possibleBlocks[topBlockIdx] << "," << clear[botBlockIdx] << ",s0).\n";
   
    clear.erase(std::begin(clear) + botBlockIdx);
    clear.push_back(possibleBlocks[topBlockIdx]);
    
    possibleBlocks.erase(std::begin(possibleBlocks) + topBlockIdx);
    
  }

    std::uniform_int_distribution<uint32_t> uniformDistBottomBlock(0, clear.size()-1);
    auto botBlockIdx = uniformDistBottomBlock(rng);
    
    std::uniform_int_distribution<uint32_t> topBlockIdxDist(0, possibleBlocks.size()-1);
    auto topBlockIdx = topBlockIdxDist(rng);

    yagiFile << "<" << "\"" << possibleBlocks[topBlockIdx] << "\",\"" << clear[botBlockIdx] << "\"" << ">};\n"; 
    gologFile << "on(" << possibleBlocks[topBlockIdx] << "," << clear[botBlockIdx] << ",s0).\n";
    
    clear.erase(std::begin(clear) + botBlockIdx);
    clear.push_back(possibleBlocks[topBlockIdx]);
    
    possibleBlocks.erase(std::begin(possibleBlocks) + topBlockIdx);
    
  
  yagiFile << "fluent fclear[{";
  for (int i=1; i<nrOfBlocks; i++)
  {
    yagiFile << "\"" << i << "\"" << ",";
  }
  yagiFile << "\"" << nrOfBlocks << "\"" << "}];\n";
  
  yagiFile << "fclear = {";

  //all that's left in 'clear' is free to move
  for (int i=0; i<clear.size()-1; i++)
  {
    yagiFile << "<" << "\"" << clear[i] << "\"" << ">,";
    gologFile << "clear(" << clear[i] << ",s0).\n";     
  }

  yagiFile << "<" << "\"" << clear[clear.size()-1] << "\"" << ">};\n"; 
  gologFile << "clear(" << clear[clear.size()-1] << ",s0).\n";


  ofstream yagiProgSearch;
  ofstream yagiProgNoSearch;
  yagiProgSearch.open(std::string{fname + "Search.y"});
  yagiProgNoSearch.open(std::string{fname + "NoSearch.y"});
  
  //since we also vary the goal we write the whole goal procedure to the file
  std::string goalYagi{""};
  std::string goalGolog{""};
  int arity;
  
  std::uniform_int_distribution<uint32_t> goalPredDist(0, 2);
  auto goalPredIdx = goalPredDist(rng);

  if (goalPredIdx == 0)
  {
    goalYagi = "onTable";
    goalGolog = "ontable(";
    arity = 1;
  }
  else if (goalPredIdx == 1)
  {
    goalYagi = "bon";
    goalGolog = "on(";
    arity = 2;
  }
  else
  {
    goalYagi = "fclear";
    goalGolog = "clear(";
    arity = 1;
  }
    
    
  std::string yagiGoalTemp {""};
  std::uniform_int_distribution<uint32_t> goalDist1(0, allBlocks.size()-1);
  auto goalIdx1 = goalDist1(rng);
  
  yagiGoalTemp = std::string{"<\""} + std::to_string(allBlocks[goalIdx1]) + std::string{"\" "};
  goalGolog += std::to_string(allBlocks[goalIdx1]);
   
  if (arity == 2)
  {
    allBlocks.erase(std::begin(allBlocks) + goalIdx1);
    std::uniform_int_distribution<uint32_t> goalDist2(0, allBlocks.size()-1);
    auto goalIdx2 = goalDist2(rng);
    
    yagiGoalTemp += ",\"" + std::to_string(allBlocks[goalIdx2]) + "\"";
    goalGolog += "," + std::to_string(allBlocks[goalIdx2]);
  
  }
  
  yagiGoalTemp += ">";
  goalYagi = yagiGoalTemp + " in " + goalYagi;
  
  goalGolog += ")";
  
  gologFile << "proc(control, while(-" << goalGolog << ", doMove)).\n";
  
  yagiProgSearch << "proc control()\n";
  yagiProgNoSearch << "proc control()\n";
  
  yagiProgSearch << "search\n";
  
  yagiProgSearch << "  while not(" << goalYagi << ") do\n";
  yagiProgNoSearch << "  while not(" << goalYagi << ") do\n";
  
  yagiProgSearch << "    doMove();\n";
  yagiProgNoSearch << "    doMove();\n";
  
  yagiProgSearch << "  end while\n";
  yagiProgNoSearch << "  end while\n";
  
  yagiProgSearch << "end search\n";
  
  yagiProgSearch << "end proc\n";
  yagiProgNoSearch << "end proc\n";
  
  yagiFile.close();
  gologFile.close();
  yagiProgSearch.close();
  yagiProgNoSearch.close();

  std::string line;
  ifstream myfile;
  myfile.open(std::string{fname + ".pl"});
  int cnt=0;
  
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::size_t found = line.find(goalGolog.substr(1,goalGolog.size()-2));
      if (found!=std::string::npos)
      {
	cnt++;
      }
    }
    myfile.close();
  }
  
  if (cnt == 2)
  {
    std::cout << "Goal initially holds!!" << std::endl;
    fine = false;
  }
  else fine = true;
  
} while(!fine);  
  
  return 0;
}