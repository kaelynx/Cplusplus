// node class tempate used to contruct lists
// Mikhail Nesterenko
// 5/01/00
// Modified by Kaelyn Campbell

#ifndef LIST_H_
#define LIST_H_

#include <iostream>


// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node{
 public:

 node(): next_(nullptr) {}

  // functions can be inlined
  T getData()const{return data_;}
  void setData(const T& data){data_=data;}

  // or can be defined outside
  node<T>* getNext() const;
  void setNext(node<T> *const);

 private:
  T data_;
  node<T> *next_;
};

//
// member functions for node
//
template <typename T>
node<T>* node<T>::getNext()const{
  return next_;
}

template<typename T>
void node<T>::setNext(node<T> *const next){
  next_=next;
}

//Collection class
template <typename T>
class Collection {
 public:
 Collection() : first_(nullptr) {}
  void addItem(T item); //takes an item as the argument and adds it to the collection doesn't check for duplicates
  void removeItem(T item); //takes item as arg and removes all (check for duplicates) instances or item from collection 5521 remove(5) removes all 5's
  T lastItem(); //returns the last item added to the collection
  void printCollection(); //prints all items in the collection (not ordered)
  //while 1 != null ptr and 2 != null ptr, iterate through and compare 
  //check if both null, 
  template<typename U>
  friend bool equal(const Collection<U>&, const Collection<U>&); //compres two collections for equality
  
 private:
  node<T> * first_;

};

//linked list, pointer to next
//Collection member functions
//add item
//head points to front
//create new node, make next point to head, point head to new node
//to front: create new node, point next to head, head points to new
//to end" iterator, iterate through and add to end
//or have tail pointer that points to last and add item to last
//try 5521355 and try to remove 1, then 5, then 2, 3, 4 
template<typename T>
void Collection<T>::addItem(T item){
  node<T> *tmp = new node<T>;
  tmp->setData(item);
  tmp->setNext(first_);
  first_ = tmp;
}

//remove item
//iterate through list, find every instance
//point to next, deallocate the one removing
//remove first: make head point to next
//remove last: set end to nullptr, deallocate
template<typename T>
void Collection<T>::removeItem(T item){
  node<T> * tmp = first_;
  while(tmp->getData() != item && tmp->getNext() != nullptr){
    tmp = tmp->getNext();
    if(tmp->getData() == item) {
    std::cout<<"here"<<std::endl;
      //get rid of it but do something else first 
      first_ = tmp->getNext();
      delete tmp;
      //      tmp = tmp->getNext();
    }
  }
}

template<typename T>
T Collection<T>::lastItem(){
  return first_->getData();
}

template<typename T>
void Collection<T>::printCollection(){
  node<T> * tmp = first_;
  while(tmp != nullptr){
    std::cout << tmp->getData();
    tmp = tmp->getNext();
  }
  std::cout<<std::endl;
}

#endif // LIST_H_