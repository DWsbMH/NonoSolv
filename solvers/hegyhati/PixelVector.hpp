#ifndef PIXELVECTOR_HPP
  #define PIXELVECTOR_HPP
  
  #include <vector>
  
  class PixelVector {
      
        unsigned int size;
          // number of pixels
        bool* pixels;
          // value of the pixels
      
      public:
        
        PixelVector(unsigned int size=0, bool filled=false);
          // Creates a vector with size and completely filled or blank
          
        PixelVector(std::vector<bool> pixels);
          // Creates a vector based on the bool vector
          
        PixelVector(std::vector<unsigned int> blankfilledList);
          // Creates a vector based on a list of the numbers of blank-filled-blank-... pixels. 
          
        PixelVector(unsigned int size, std::vector<unsigned int> filledList, bool rightmost=true);
          // Creates a vector with size, arranging a list of filled pixels totally to the left or right
          
        PixelVector(unsigned int size, unsigned int listsize, unsigned int* filledList, bool rightmost=true);
          // Same as previous.
          
        PixelVector(const PixelVector& other);
          // Simple copy constructor
        
        PixelVector& operator = (const PixelVector& other);
          // copies the other pixelvector
              
        ~PixelVector();
          // Simple destructor
        
        unsigned int getSize() const;
          // returns the size of the vector
          
        bool operator[](unsigned int pixel) const;
          // returns the value of a pixel if in range, otherwise false.
          
        std::vector<bool> getPixelList() const;
          // returns the vector in the form of a bool vector
          
        std::vector<int> getBlankFilledList() const;
          // returns the vector in the form of a blank-filled-blank list. Always have odd number of element.
          
        bool isLeftMost() const;
          // returns true, if none of the filled pixels could be moved to the left withouth merging them
          
        bool isRightMost() const;
          // returns true, if none of the filled pixels could be moved to the right withouth merging them
          
        void operator++(int); 
          // increasis the vector as if it were a number. Overflows.
          
        bool isAllBlank() const;
          // returns true, if all the pixels are blank
          
        bool isAllFilled() const;
          // returns true, if all the pixels are filled
          
        bool shiftToLeftMost();
          // if it is not a leftmost pixelvector, it shifts to the next one towards the leftmost, and returns true. Otherwise does nothing and returns false

  };
  
#endif
