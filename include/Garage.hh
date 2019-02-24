#ifndef GARAGE_HH_
#define GARAGE_HH_

#include <vector>
#include "Car.hh"

class Garage
{
public:
  Garage();
  Garage(const json &data);

  Car &getBox(size_t index) const;
  size_t getSize() const;
  size_t getBoxCount() const;

  bool addCar(Car &car);
  void sellCar(size_t index);

private:
  std::vector<std::shared_ptr<Car>> _boxs;
  size_t _boxCount;
};

void to_json(json& j, const Garage& garage);

#endif /* !GARAGE_HH_ */