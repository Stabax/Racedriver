#ifndef PART_HPP_
#define PART_HPP_

#include <vector>
#include <DataFile.hh>
#include <Menu.hh>
#include "Units.hpp"

#define ID_SEPARATOR '.'

/*!
 * @brief Base class inherited by any part
 */
class Part
{
public:
  enum Type {
    TCar,
    TEngine,
    TSpoiler,
    TTires
  };

  Part(const json &data, Type t) //build from json
   : type(t)
  {
    if (data.find("name") != data.end()) name = data["name"].get<std::string>();
    if (data.find("manufacturer") != data.end()) manufacturer = data["manufacturer"].get<std::string>();
    if (data.find("socket") != data.end()) socket = data["socket"].get<std::string>();
    if (data.find("mass") != data.end()) mass = omni::Kilogram(data["mass"].get<int>());
    if (data.find("price") != data.end()) price = data["price"].get<int>();
  }

  virtual ~Part() { }

  const std::string getId() const
  {
    return (manufacturer+ID_SEPARATOR+name);
  }

  virtual std::string info()
  {
    return (manufacturer+" "+name);
  }

  bool operator==(const Part &part)
  {
    return (getId() != part.getId());
  }

  std::string manufacturer;
  std::string name;
  std::string socket;
	omni::Kilogram mass;
	int price;
  Type type;
};

#endif /* !PART_HPP_ */