#ifndef WORDL_H_
#define WORDL_H_

#include <iostream>
#include <string>

class WordOccurrence {
 public:
 WordOccurrence(const std::string& word="", int num=0):word_(word), num_(num) {}
  bool matchWord(const std::string &); // returns true if word matches stored
  void increment(); // increments number of occurrences
  std::string getWord() const { return word_; } 
  int getNum() const { return num_; }
  
 private:
  std::string word_;
  int num_;
};

class WordList{
public:
  // add copy constructor, destructor, overloaded assignment
  WordList();
  WordList(const WordList &cpy);
  ~WordList();
  WordList &operator=(const WordList &rhs);

  // implement comparison as friend
  friend bool equal(const WordList&, const WordList&);

  void addWord(const std::string &);
  void print();
  void sortList();
private:
  WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
  // may or may not be sorted
  int size_;
};

bool equal(const WordList& lhs, const WordList& rhs){
  if(lhs.size_ == rhs.size_){
    for(int i = 0; i < lhs.size_; ++i){
      if(lhs.wordArray_[i].getWord() == rhs.wordArray_[i].getWord() 
	 && lhs.wordArray_[i].getNum() == rhs.wordArray_[i].getNum()) {
	return true;
      }
    }
  }
  return false;
}

#endif
