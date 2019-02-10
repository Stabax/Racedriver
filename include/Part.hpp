#ifndef PART_HPP_
#define PART_HPP_

#include <vector>
#include <omniunit.hh>
#include "DataFile.hh"
#include "Utils.hh"
#include "Menu.hh"

#define ID_SEPARATOR '.'

/*!
 * @brief Base class inherited by any part
 */
class Part
{
public:
  Part() {}; //Dummy for lua
  Part(const json &data) //build from json
  {
    if (data.find("name") != data.end()) name = data["name"].get<std::string>();
    if (data.find("mass") != data.end()) mass = omni::Kilogram(data["mass"].get<int>());
    if (data.find("manufacturer") != data.end()) manufacturer = data["manufacturer"].get<std::string>();
    if (data.find("rank") != data.end()) rank = charToRank(data["rank"].get<std::string>()[0]);
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
	omni::Kilogram mass;
  Rank rank;
};

#endif /* !PART_HPP_ */