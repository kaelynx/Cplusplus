// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Modified by Kaelyn Campbell

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
  double weight; // oz
  string color;  // red or green
  void print() const { cout << color << ", " <<  weight << endl; }
};



Apples generateRandApple();
bool apple2apple(const Apples & a, const Apples & b);
bool compareColor(Apples a);
bool findRed(Apples a);

int main(){
  srand(time(nullptr));

  cout << "Input crate size: ";
  int size;
  cin >> size;

  vector <Apples> crate(size);

  // assign random weight and color to apples in the crate
  generate(crate.begin(), crate.end(), generateRandApple);

 
  cout << "Enter weight to find: ";
  double toFind;
  cin >> toFind;

  int cnt = count_if(crate.begin(), crate.end(), [toFind] (Apples a) { return a.weight > toFind; });
  cout << "There are " << cnt << " apples heavier than " 
       << toFind << " oz" <<  endl;

  // find_if()
  cout << "at positions ";
  auto itr = find_if(crate.begin(), crate.end(), 
		     [toFind] (Apples a) { return a.weight > toFind; });
  if(itr != crate.end()) {
    do{
      cout << itr - crate.begin() << ", ";
      itr = find_if(itr + 1, crate.end(), [toFind] (Apples a) { return a.weight > toFind; });
    }while(itr != crate.end());
  }
  cout << endl;


  // max_element()
  Apples heaviest = *max_element(crate.begin(), crate.end(), apple2apple);
  cout << "Heaviest apple weighs: " << heaviest.weight << " oz" << endl;


  // for_each() or accumulate()
  double sum = accumulate(crate.begin(), crate.end(), 0.0, [] (double i, const Apples & a) { return i += a.weight; });
  cout << "Total apple weight is: " << sum << " oz" << endl;

  // transform();
  cout << "How much should they grow: ";
  double toGrow;
  cin >> toGrow;
  transform(crate.begin(), crate.end(), crate.begin(), [&toGrow] (Apples a) 
	    { 
	      a.weight += toGrow; 
	      return a; 
	    });

  // remove_if()
  cout << "Input minimum acceptable weight: ";
  double minAccept;
  cin >> minAccept;
  crate.erase(remove_if(crate.begin(), crate.end(), [=] (Apples a) 
			{
			  return a.weight < minAccept;
			}), crate.end());
  cout << "removed " << size - crate.size() << " elements" << endl;


  // bubble sort, replace with sort()
  sort(crate.begin(), crate.end(), apple2apple);

  // moving all red apples from crate to peck
  // remove_copy_if() with back_inserter()/front_inserter() or equivalents
  deque<Apples> peck;
  remove_copy_if(crate.begin(), crate.end(), back_inserter(peck), findRed);
  crate.erase(remove_if(crate.begin(), crate.end(), compareColor), crate.end());

  // for_each() possibly
  cout << "apples in the crate"<< endl;
  for_each(crate.begin(), crate.end(), [=] (Apples e) { e.print(); });
  cout << endl;

  // for_each() possibly
  cout << "apples in the peck"<< endl;

  for_each(peck.begin(), peck.end(), [=] (Apples e) { e.print(); });

  const int space=3; 
  
  cout << "\nevery " << space << "\'d apple in the peck"<< endl;
  
  // replace with advance()/next()/distance()
  // no pointer arithmetic
  auto it=peck.cbegin(); int i = 0; 

  while(i < distance(it, peck.cend())){
    if(it + 3 != peck.cend()){
      advance(it, space);
      it->print();
    }
    ++i;
  }
}

Apples generateRandApple(){
  const double minWeight = 8.;
  const double maxWeight = 3.;
  
  Apples a;
  a.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
  a.color = rand() % 2 == 1 ? "green" : "red";
  return a;
}

bool apple2apple(const Apples & a, const Apples & b) {
  return a.weight < b.weight;
}

bool compareColor(Apples a){
  return a.color == "red";
}

bool findRed(Apples a){
  return a.color == "green";
}
