#ifndef PART_HPP_
#define PART_HPP_

#include <vector>
#include "DataFile.hh"

#define ID_SEPARATOR '.'

//Forward declaring parts
class Tires;
class AirIntake;
class Spoiler;

enum Rank {
  D,
  C,
  B,
  A,
  S
};

Rank charToRank(char c)
{
  switch (c)
  {
    case 'D':
      return (D);
    case 'C':
      return (C);
    case 'B':
      return (B);
    case 'A':
      return (A);
    case 'S':
      return (S);
    default:
      throw std::runtime_error("No such rank");
  }
}

class Part
{
public:
  Part(const json &data)
  : manufacturer(data["manufacturer"].get<std::string>()), name(data["name"].get<std::string>()), rank(charToRank(data["name"].get<std::string>()[0]))
  {
  }

  virtual ~Part() { }

  const std::string getId()
  {
    return (manufacturer+ID_SEPARATOR+name);
  }

  template <typename T>
  static const std::string getCollectionPath()
  {
    std::string path = "./Data/Parts/";
    if (std::is_same<T, Tires>::value) path += "Tires";
    else if (std::is_same<T, AirIntake>::value) path += "AirIntake";
    else if (std::is_same<T, Spoiler>::value) path += "Spoiler";
    else throw std::runtime_error("Unknown part type");
    return (path+".json");
  }

  template <typename T>
  static void loadCollection(std::map<std::string, T> &collection)
  {
    std::string path;
    try {
      path = getCollectionPath<T>();
    } catch (const std::exception &e) {
      throw std::runtime_error("Cannot load collection:"+std::string(e.what()));
    }
    DataFile collectionFile(path);

    if (!collectionFile.load())
    {
      throw std::runtime_error("Cannot load collection file:"+path);
    }
    const json &data = collectionFile.getData();
    for (size_t i = 0; i < data["collection"].size(); i++)
    {
      T obj(data["collection"][i]);
      collection.emplace(dynamic_cast<Part>(obj).getId(), obj);
    }
  }

  const std::string manufacturer;
  const std::string name;
  const Rank rank;
};

#endif /* !PART_HPP_ */