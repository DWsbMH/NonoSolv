#include "PixelVector.hpp"

PixelVector::PixelVector(unsigned int size, bool filled)
:size(size) {
  pixels = new bool[size];
  for(unsigned int i=0;i<size;i++) pixels[i]=filled;
}
  
PixelVector::PixelVector(std::vector<bool> pixels)
:size(pixels.size()){
  this->pixels = new bool[size];
  for(unsigned int i=0;i<size;i++) this->pixels[i]=pixels[i];
}


PixelVector::PixelVector(std::vector<unsigned int> blankfilledList) {
  size=0;
  for(unsigned int i=0;i<blankfilledList.size();i++) size+=blankfilledList[i];
  pixels = new bool[size];
  int next=0;
  for(unsigned int i=0;i<blankfilledList.size();i++) 
    for (unsigned int j=0;j<blankfilledList[i];j++) pixels[next++]=i%2;
}

PixelVector::PixelVector(unsigned int size, std::vector<unsigned int> filledList, bool rightmost)
:size(size) {
  pixels = new bool [size];
  int free=size-(filledList.size()-1);
  for (unsigned int i=0;i<filledList.size();i++) free-=filledList[i];
  if (free<0) {
    delete [] pixels;
    size-=free;
    pixels = new bool [size];
    free=0;
  }
  int next=0;
  if(rightmost) for(int i=0;i<free;i++) pixels[next++]=false;
  for(unsigned int i=0;i<filledList.size();i++) {
    if(i) pixels[next++] = false;
    for(unsigned int j=0;j<filledList[i];j++) pixels[next++]=true;
  }
  if(!rightmost) for(int i=0;i<free;i++) pixels[next++]=false;
}

PixelVector::PixelVector(unsigned int size, unsigned int listsize, unsigned int* filledList, bool rightmost)
:size(size) {
  pixels = new bool [size];
  int free=size-(listsize-1);
  for (unsigned int i=0;i<listsize;i++) free-=filledList[i];
  if (free<0) {
    delete [] pixels;
    size-=free;
    pixels = new bool [size];
    free=0;
  }
  int next=0;
  if(rightmost) for(int i=0;i<free;i++) pixels[next++]=false;
  for(unsigned int i=0;i<listsize ;i++) {
    if(i) pixels[next++] = false;
    for(unsigned int j=0;j<filledList[i];j++) pixels[next++]=true;
  }
  if(!rightmost) for(int i=0;i<free;i++) pixels[next++]=false;
}

PixelVector::PixelVector(const PixelVector& other)
:size(other.size) {
  pixels = new bool[size];
  for(unsigned int i=0;i<size;i++) pixels[i]=other.pixels[i];
}

PixelVector& PixelVector::operator = (const PixelVector& other){
  delete [] pixels;
  pixels = new bool[other.size];
  for(unsigned int i=0;i<size;i++) pixels[i]=other.pixels[i];
  return *this;
}


PixelVector::~PixelVector(){
  delete [] pixels;
}


unsigned int PixelVector::getSize() const {return size;}

bool PixelVector::operator[](unsigned int pixel) const { 
  if (pixel < size) return pixels[pixel];
  else return false;
}

std::vector<bool> PixelVector::getPixelList() const {
  std::vector<bool> toReturn;
  for(unsigned int i=0;i<size;i++) toReturn.push_back(pixels[i]);
  return toReturn;
}


std::vector<int> PixelVector::getBlankFilledList() const {
  std::vector<int> toReturn;
  bool filled=false;
  int count=0;  
  for(unsigned int next=0;next<size;next++){
    if (pixels[next]==filled) count++;
    else {
      toReturn.push_back(count);
      count=1;
      filled = !filled;
    }
  } 
  toReturn.push_back(count);
  if (filled) toReturn.push_back(0);
  return toReturn;
}


bool PixelVector::isLeftMost() const {
  if (!pixels[0]) return false;
  int temp=size-1;
  while (!pixels[temp]) temp--;
  while (temp>0)
    if (!pixels[temp] && !pixels[temp-1]) return false;
    else temp--;
  return true;
}

bool PixelVector::isRightMost() const {
  if (!pixels[size-1]) return false;
  unsigned int temp=0;
  while (!pixels[temp]) temp++;
  while (temp<size-1)
    if (!pixels[temp] && !pixels[temp+1]) return false;
    else temp++;
  return true;
}

void PixelVector::operator++(int) {
  int temp=size-1;
  while (temp && pixels[temp]) pixels[temp--]=false;
  if (temp) pixels[temp]=true;
}


bool PixelVector::isAllBlank() const {
  for(unsigned int i=0;i<size;i++) if(pixels[i]) return false;
  return true;
}

bool PixelVector::isAllFilled() const {
  for(unsigned int i=0;i<size;i++) if(!pixels[i]) return false;
  return true;
}

bool PixelVector::shiftToLeftMost() {
  if(isLeftMost()) return false;
  std::vector<int> blankfilledList=getBlankFilledList();
  
  blankfilledList[0]++;
  blankfilledList.back()++;
    
  unsigned int  blank = blankfilledList.size()-3;
  
  while(blankfilledList[blank]==1) blank-=2;
    
  blankfilledList[blank]--;
  blankfilledList[blank+2]++;
  if(blank!=blankfilledList.size()-3) {
    blankfilledList[blank+2]+=blankfilledList.back()-1;
    blankfilledList.back()=1;
  }
         
  blankfilledList[0]--;
  blankfilledList.back()--;
    
  int next=0;
  for(unsigned int i=0;i<blankfilledList.size();i++) 
    for (int j=0;j<blankfilledList[i];j++) pixels[next++]=i%2;
  return true;
}   
