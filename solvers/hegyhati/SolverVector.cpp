#include "SolverVector.hpp"
#include <map>

SolverVector::SolverVector(unsigned int size, std::vector<unsigned int> puzzle, unsigned int cacheSize)
:count(puzzle.size()),size(size),cacheSize(cacheSize),cacheComplete(false),externalChange(true) {
  fields = new state[size];
  for(unsigned int i=0;i<size;i++) fields[i]=UNCERTAIN;
  this->puzzle = new unsigned int [count];
  for(unsigned int i=0; i<count; i++)
    this->puzzle[i]=puzzle[i];  
}


SolverVector::~SolverVector() {delete [] fields; delete [] puzzle;}


std::vector<state> SolverVector::getState() const {
  std::vector<state> toReturn;
  for(unsigned int i=0; i<size; i++)
    toReturn.push_back(fields[i]);
  return toReturn;
}

std::list<PixelVector> SolverVector::getCache() const {
  return candidates;
}        


bool SolverVector::isSolved() const {
  if (cacheComplete && candidates.size()==1) return true;
  for(unsigned int i=0; i<size; i++)
    if(fields[i]==UNCERTAIN) return false;
  return true;
}

bool SolverVector::isIncompatible(const PixelVector& solution) const {
  if(size!=solution.getSize()) return true;
  for(unsigned int i=0; i<size; i++) 
    if(fields[i]==UNCERTAIN) continue;
    else if (fields[i]==FILLED && !solution[i]) return true;
    else if (fields[i]==BLANK && solution[i]) return true; 
  return false;
}

void SolverVector::setCacheSize(unsigned int newSize){
  cacheSize = newSize;
  if (candidates.size()>cacheSize){
    cacheComplete=false;
    candidates.resize(cacheSize);
  }
}

void SolverVector::setField(unsigned int index, bool filled){
  if (index>=0 && index <size) {
    fields[index] = filled?FILLED:BLANK;
    externalChange=true;    
  }
}

bool SolverVector::updateCache() {
  if (cacheComplete & !externalChange) return true;
  
  PixelVector candidate(size,count,puzzle,true);
  
  if(!candidates.empty()){
    candidate = candidates.back();
    if (externalChange) {
      auto it = candidates.begin();
      while (it!=candidates.end())
        if(isIncompatible(*it)) it=candidates.erase(it);
        else it++;
    }
    if(!candidate.shiftToLeftMost()) return cacheComplete = true;
  } 
  
 while (candidates.size()<cacheSize) {
    if(!isIncompatible(candidate)) candidates.push_back(candidate);    
    if(!candidate.shiftToLeftMost()) return cacheComplete=true;
  }
  
  return cacheComplete=false;
}

bool SolverVector::isChanged() const {
  return externalChange;
}

ChangeList SolverVector::check() {
  ChangeList toReturn;
  updateCache();
  externalChange=false;
  
  std::map<unsigned int,bool> uncertains;
  PixelVector candidate(size,count,puzzle,true);
  
  if(candidates.size()){
    candidate=candidates.back();
    for(unsigned int i=0; i<size; i++)
      if(fields[i]==UNCERTAIN) uncertains[i]=candidates.back()[i];
    for(auto scandidate: candidates){
      if (uncertains.size()==0) return toReturn;
      for(auto it=uncertains.begin(); it!=uncertains.end(); )
        if (it->second != scandidate[it->first]) it=uncertains.erase(it);
        else it++;
    }
  } else {     
    while(isIncompatible(candidate)) candidate.shiftToLeftMost(); 
      //NOTE: will end up in infinite loop, if there is no feasible PixelVector
    for(unsigned int i=0; i<size; i++)
      if(fields[i]==UNCERTAIN) uncertains[i]=candidate[i];        
  }
  
  do{
    candidate.shiftToLeftMost();
    if (uncertains.size()==0) return toReturn;
    for(auto it=uncertains.begin(); it!=uncertains.end(); )
      if (it->second != candidate[it->first]) it=uncertains.erase(it);
      else it++;
  } while (!candidate.isLeftMost());
  
  
  for(auto it=uncertains.begin(); it!=uncertains.end(); it++)
    if(it->second) {
      fields[it->first]=FILLED;
      toReturn.newFilled.push_back(it->first);
    } else {
      fields[it->first]=BLANK;
      toReturn.newBlank.push_back(it->first);
    }
   
  
  return toReturn;
}

ChangeList SolverVector::checkWithinCache(){
  ChangeList toReturn;
  
  if (updateCache()){ 
    externalChange=false;
    std::map<unsigned int,bool> uncertains;
    for(unsigned int i=0; i<size; i++)
      if(fields[i]==UNCERTAIN) uncertains[i]=candidates.back()[i];
    
    for(auto candidate: candidates){
      if (uncertains.size()==0) return toReturn;
      for(auto it=uncertains.begin(); it!=uncertains.end(); )
        if (it->second != candidate[it->first]) it=uncertains.erase(it);
        else it++;
    }
    externalChange=false;
    for(auto it=uncertains.begin(); it!=uncertains.end(); it++)
      if(it->second) {
        fields[it->first]=FILLED;
        toReturn.newFilled.push_back(it->first);
      } else {
        fields[it->first]=BLANK;
        toReturn.newBlank.push_back(it->first);
      }
  } 
  
  return toReturn;
}
