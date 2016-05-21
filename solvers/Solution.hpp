#ifndef SOLUTION_HPP
  #define SOLUTION_HPP
  
  #include "Puzzle.hpp"
  #include <vector>
  
  class Position {
    public:
      unsigned int row;
      unsigned int column;
      Position(unsigned int row, unsigned int column);
  };
      
      
  class Solution {
      
      bool badposition;
      bool** pixels;
      unsigned int rowSize,columnSize;      
      
    public:
      
      Solution(unsigned int rowSize, unsigned int columnSize);
      ~Solution();
      bool isSolutionOf(const Puzzle& puzzle) const;
      bool& operator [] (Position position);      
      
  };
  
#endif
