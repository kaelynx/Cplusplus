#include <iostream>
#include <vector>
#include <cstdlib>
#include "abstractFactory.hpp"

// product methods
Subaru::Subaru(){
  static std::vector<std::string> models = 
    {"WRX", "Impreza", "Outback", "Crosstrek"};
  make_ = "Subaru";
  // choose a random model from models vector
  model_ = models[rand() % models.size()];
}

Dodge::Dodge(){
  static std::vector<std::string> models = 
    {"Charger", "Journey", "Durango", "Ram 1500"};
  make_ = "Dodge";
  model_ = models[rand() % models.size()];
}

// factory methods
AbstractCar* CarFactory::getNewCar() {
  ++totalCars_;
  return createNewCar();
}

AbstractCar* SubaruFactory::createNewCar(){
  return new Subaru();
}

AbstractCar* DodgeFactory::createNewCar(){
  return new Dodge();
}

// car dealer
CarDealer::CarDealer(){
  // four factories with random total cars
  factories_.push_back(new SubaruFactory("Subaru Factory", "Akron, Ohio", rand() % 4));
  factories_.push_back(new SubaruFactory("Subaru Factory", "Pittsburgh, PA", rand() % 4));
  factories_.push_back(new DodgeFactory("Dodge Factory", "Cuyahoga Falls, Ohio", rand() % 4));
  factories_.push_back(new DodgeFactory("Dodge Factory", "Pittsburgh, PA", rand() % 4));
  for(int i = 0; i < lotSize_; ++i){
    carsForSale_[i] = factories_[rand() % factories_.size()]->getNewCar();
  }
}

// finds the least busy factory
CarFactory* CarDealer::getLeastBusy(const std::vector<CarFactory*> &factories){
  if(factories.size() == 0) return nullptr;
  auto leastBusy = factories[0];
  for(int i = 1; i != factories.size(); ++i) {
    if(factories[i]->getTotalCars() < leastBusy->getTotalCars())
      leastBusy = factories[i];
  }
  std::cout << "Ordering from: " << leastBusy->getName() << std::endl
	    << "Located in: " << leastBusy->getLocation() << std::endl
	    << "With " << leastBusy->getTotalCars() << " total cars in production." << std::endl;
  return leastBusy;
}

// global pointer
CarDealer* carDealerPtr = nullptr;

// buys the car if Subaru
void buySubaru(){
  if(carDealerPtr == nullptr) carDealerPtr = new CarDealer();
  AbstractCar * toBuy = carDealerPtr->testDrive();
  // test drive all cars on lot unless Subaru found
  for(int i = 0; i < carDealerPtr->getLotSize(); ++i){
    std::cout << "Test driving: " 
	      << toBuy->getMake() << " " 
	      << toBuy->getModel() << std::endl;
    if(toBuy->getMake() == "Subaru"){
      std::cout<< "Buying it!!" << std::endl;
      carDealerPtr->buyCar();
      break;
    } else {
      std::cout<< "Did not like it." << std::endl;
      toBuy = carDealerPtr->testDrive();
    }
  }
}

int main() {
  srand(time(nullptr));
  buySubaru();
}
