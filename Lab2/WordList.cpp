#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "WordList.h" // class definitions

bool WordOccurrence::matchWord(const std::string & s) {
  if(word_ == s){
    return true;
  }
  else
    return false;
}

void WordOccurrence::increment() {
  ++num_;
}

WordList::WordList(){
  size_ = 0;
  wordArray_ = new WordOccurrence[size_];
}

WordList::WordList(const WordList &cpy){
  size_ = cpy.size_;
  wordArray_ = new WordOccurrence[size_];
  for(int i = 0; i < size_; ++i)
    wordArray_[i] = cpy.wordArray_[i];
}

WordList::~WordList(){
  delete [] wordArray_;
}

WordList& WordList::operator=(const WordList &rhs){
  if(this != &rhs){
    delete [] wordArray_;
    size_ = rhs.size_;
    wordArray_ = new WordOccurrence[size_];
    for(int i = 0; i < size_; ++i)
      wordArray_[i] = rhs.wordArray_[i];
  }
  /*
  WordList tmp(rhs);
  std::swap(wordArray_, rhs.wordArray_);
  std::swap(size_, rhs.size_);
  */
  return *this; 
}

void WordList::addWord(const std::string & w){
  //if the word exists increment counter
  bool found = false;
  for(int i = 0; i < size_; ++i){
    if(wordArray_[i].matchWord(w)){
      wordArray_[i].increment();
      found = true;
    }
  }
  if(!found){
    ++size_;
    //if new make temp array of size + 1
    WordOccurrence firstOcc(w);
    WordOccurrence *tmp = new WordOccurrence[size_];
    //copy old array to temp array
    int count = 0;
    for(int j = 0; j < (size_ - 1); ++j){
      tmp[j] = wordArray_[j];
      ++count;
    }
    //add new word to temp
    tmp[count] = firstOcc;
    //delete old pointer and point to new
    delete [] wordArray_;
    wordArray_ = new WordOccurrence[size_];
    for(int k = 0; k < size_; ++k){
      wordArray_[k] = tmp[k];
    }
    delete [] tmp;
  }
}

void WordList::print(){
  std::string word;
  int num;
  for(int i = 0; i < size_; ++i){
    std::cout<< "Word: " << wordArray_[i].getWord() << " Counts: " 
	     << (wordArray_[i].getNum()+1) << std::endl;
  }
}

void WordList::sortList(){
  WordList temp(*this);
  int max = 0;
  //find the max num 
  for(int i = 0; i < size_; ++i){
    if(wordArray_[i].getNum() >= max){
      max = temp.wordArray_[i].getNum();
    }
  }

  for(int j = 0; j < size_;){
    for(int k = 0; k < size_; ++k){
      //if max assign to temp and move to temp[next]
      if(wordArray_[k].getNum() == max){
	temp.wordArray_[j] = wordArray_[k];
	++j;
      }
    }
    //decrement to find next max
    --max;
  }
  temp.print();
}

int main(int argc, char * argv[]){
  //check for enough arguments
  if(argc != 2) {
    std::cerr << argv[0] << " invalid number of arguments." << '\n';
    return 1;
  }
  //open file
  std::ifstream in(argv[1]);
  if(!in) { std::cerr << "Couldn't open " << argv[1] << "\n"; exit(1); }  
  WordList myList;
  std::string line;
  std::string temp;
  while(in >> line){
    int length = line.length();
    for(int i = 0; i < length; ++i){
      if(ispunct(line[i])){
	//remove punct from string
	line.erase(i--, 1);
	length = line.size();
	++i;
      }
      //add to temp
      if(!ispunct(line[i]) && isalpha(line[i]))
      temp += line[i];
    }
    //add to list and clear temp
      myList.addWord(temp);
      temp = "";
  } 
  
  myList.sortList();
  in.close();
}

