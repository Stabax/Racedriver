#include "Garage.hh"

Garage::Garage(const json &data)
{
  for (size_t i = 0; i < data.size(); i++)
  {
    _boxs.push_back(std::make_shared<Car>(data[i]));
  }
}