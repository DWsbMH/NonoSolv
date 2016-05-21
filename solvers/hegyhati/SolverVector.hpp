#ifndef SOLVERVECTOR_HPP
  #define SOLVERVECTOR_HPP
  
  #include "PixelVector.hpp"
  #include <vector>
  #include <list>
  
  enum state {FILLED, BLANK, UNCERTAIN};
  
  
  class ChangeList {
    public:
      std::vector<unsigned int> newFilled;
      std::vector<unsigned int> newBlank;
  };
  
  
  class SolverVector{
    
      unsigned int count;
        // number of the cohesive parts in the puzzle
      unsigned int* puzzle;
        // the size of the cohesive parts
      unsigned int size;
        // number of the pixels
      state* fields;
        // state of the pixels
      
      std::list<PixelVector> candidates;
        // cache for possible candidates
      unsigned int cacheSize;
        // maximal capacity for the cache
      bool cacheComplete;
        // is true, when all the possible candidates are already in the cache
      
      bool externalChange;
        // true, if there was an external change since last check
      
      
    public:
    
      SolverVector(unsigned int size, std::vector<unsigned int> puzzle, unsigned int cacheSize=0);
        // Creates a SolverVector with the puzzle, and cache, etc. Cache is not filled.
      ~SolverVector();
        // Simple destructor
      
      std::vector<state> getState() const;
        // Returns the current state
        
      std::list<PixelVector> getCache() const;
        // Returns the cache, only for development TODO: remove
      
      bool isSolved() const;
        // Returns true, if all of the pixels are decided
        
      bool isIncompatible(const PixelVector& solution) const;
        // Returns true, if the given solution can not be derived from the current SolverVerctor
      
      void setCacheSize(unsigned int newSize);
        // Changes the maximal size of the cache. If the new limit is lower than the current size, the last items are removed.
        
      void setField(unsigned int index, bool filled);
        // Manually sets one field to a specific value
        
      bool updateCache();
        // Removes the incompatible items in the cache, and then fills it up until the limit is reached. If all of the candidates can be stored, the cache becomes complete, and the function returns true.
      
      bool isChanged() const;
        // Returns true, if there was a change since the last check.
        
      ChangeList check();
        // Checks if there is a new resolution among the compatible candidates, and returns the new changes. Updates the cache in the process.
        
      ChangeList checkWithinCache();   
        // Update the cache and checks if there is a new resolution if it is complete. Returns the new changes.
      
      
  };

#endif
