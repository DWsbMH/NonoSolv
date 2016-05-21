#include "Puzzle.hpp"

bool Puzzle::checkBasicConsistency(){
  int filled=0;
  unsigned int length;
  
  for (auto row: rows){
    length=0;
    for(auto item: row)
      length+=item;
    if(length + row.size() > columns.size() + 1) return false;
    filled += length;    
  }
  
  for (auto column: columns){
    length=0;
    for(auto item: column)
      length+=item;
    if(length + column.size() > rows.size() + 1) return false;
    filled -= length;    
  }
  
  return (filled==0);
}
