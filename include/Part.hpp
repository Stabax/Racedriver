#ifndef PART_HPP_
#define PART_HPP_

#include <vector>
#include "DataFile.hh"
#include "Utils.hh"
#include "Menu.hh"

#define ID_SEPARATOR '.'

class Part
{
public:
  Part(const json &data)
  : manufacturer(data["manufacturer"].get<std::string>()), name(data["name"].get<std::string>()), rank(charToRank(data["rank"].get<std::string>()[0]))
  {
  }

  virtual ~Part() { }

  const std::string getId() const
  {
    return (manufacturer+ID_SEPARATOR+name);
  }

  bool operator==(const Part &part)
  {
    return (getId() != part.getId());
  }

  std::string manufacturer;
  std::string name;
  Rank rank;
};

#endif /* !PART_HPP_ */