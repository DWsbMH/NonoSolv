#include "Solution.hpp"

Position::Position(unsigned int row, unsigned int column)
:row(row),column(column){}


Solution::Solution(unsigned int rowSize, unsigned int columnSize)
:rowSize(rowSize),columnSize(columnSize){
  pixels = new bool* [rowSize];
  for (unsigned int i=0;i<rowSize;i++){
    pixels[i] = new bool [columnSize];
    for (unsigned int j=0;j<columnSize;j++)
      pixels[i][j]=false;
  }
  badposition=false;
}

Solution::~Solution(){
  for (unsigned int i=0;i<rowSize;i++) delete [] pixels[i];
  delete [] pixels;
}

bool& Solution::operator [] (Position position){
  if (position.row<rowSize && position.column<columnSize)
    return pixels[position.row][position.column];
  else return badposition;
}


bool Solution::isSolutionOf(const Puzzle& puzzle) const{
  //TODO do the check
  return true;
}

