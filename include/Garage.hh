#ifndef GARAGE_HH_
#define GARAGE_HH_

#include <vector>
#include "Car.hh"

class Garage
{
public:
  Garage(const json &data);

private:
  std::vector<std::shared_ptr<Car>> _boxs;
};

#endif /* !GARAGE_HH_ */