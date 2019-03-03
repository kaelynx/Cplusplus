/*
 A simple code that demonstrates the Abstract Factory Design Pattern.
*/

#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <iostream>
#include <string>
#include <vector>

// abstract product
class AbstractCar {
public:
  std::string getMake() { return make_; }
  std::string getModel() { return model_; }
protected:
  std::string make_;
  std::string model_;
};

// concrete product
class Subaru : public AbstractCar {
public:
  Subaru();
};

// concrete product
class Dodge : public AbstractCar {
public:
  Dodge();
};

// abstract Factory
class CarFactory {
public:
  CarFactory(std::string name, std::string loc, int totalCars) : name_(name), loc_(loc), totalCars_(totalCars){}
  std::string getName() { return name_; }
  std::string getLocation() { return loc_; }
  int getTotalCars() { return totalCars_; }
  AbstractCar* getNewCar();
  virtual ~CarFactory(){}

protected: 
  virtual AbstractCar* createNewCar() = 0;

private:
  std::string name_;
  std::string loc_;
  int totalCars_;
};

// concrete Subaru factory
class SubaruFactory : public CarFactory {
public:
  SubaruFactory(std::string name = "", std::string loc = "", int totalCars = 0) 
    : CarFactory(name, loc, totalCars){}
protected:
  AbstractCar* createNewCar();
};

// concrete Dodge factory
class DodgeFactory : public CarFactory {
public:
  DodgeFactory(std::string name, std::string loc = "", int totalCars = 0) 
    : CarFactory(name, loc, totalCars){}
protected:
  AbstractCar* createNewCar();
};

class CarDealer {
public:
  CarDealer();
  AbstractCar* buyCar(){
    AbstractCar* bought = carsForSale_[currentPos_];
    //replace bought car with car from least busy factory
    carsForSale_[currentPos_] = getLeastBusy(factories_)->getNewCar(); 
    // reset position
    currentPos_ = -1;
    return bought;
  }
  AbstractCar* testDrive(){
    AbstractCar* temp = getNextCar();
    return temp;
  }
  AbstractCar* getNextCar(){
    if(currentPos_ < 2){
      // move to next position
      ++currentPos_;
      return carsForSale_[currentPos_];
    } else {
      // reached the end
      return carsForSale_[currentPos_];
    }
  }
  CarFactory* getLeastBusy(const std::vector<CarFactory*> &factories);
  int getLotSize() { return lotSize_; }

private:
  const int lotSize_ = 3;
  int currentPos_ = -1;
  AbstractCar* carsForSale_[3];
  std::vector<CarFactory*> factories_;
};

#endif
