#ifndef GARAGE_HH_
#define GARAGE_HH_

#include <vector>
#include "Car.hh"

class Garage
{
public:
  Garage();
  Garage(const json &data);

  Car &selectCar() const;
  Car &getBox(int index) const;
  size_t getBoxCount() const;

  void displayBoxList();
  void displayBoxDetail(int index);

private:
  std::vector<std::shared_ptr<Car>> _boxs;
};

void to_json(json& j, const Garage& garage);

#endif /* !GARAGE_HH_ */