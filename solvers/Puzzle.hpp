#ifndef PUZZLE_HPP
  #define PUZZLE_HPP
  
  #include <vector>
  
  class Puzzle{
    public:
      std::vector< std::vector <unsigned int> > rows;
      std::vector< std::vector <unsigned int> > columns;
    
      bool checkBasicConsistency();
        // Checks if the number of filled pixels in the rows are the same as in the columns. checks if there are any longer rows or columns than the number of columns or rows.
  };


#endif
