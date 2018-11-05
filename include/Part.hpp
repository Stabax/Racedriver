#ifndef PART_HPP_
#define PART_HPP_

#include <vector>
#include "DataFile.hh"
#include "Utils.hh"
#include "Menu.hh"

#define ID_SEPARATOR '.'

//Forward declaring parts
class Car;
class Engine;
class Tires;
class AirIntake;
class Spoiler;

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

  template <typename T>
  static const std::string getCollectionPath()
  {
    if (std::is_same<T, Car>::value)
    {
      return ("./Data/Cars.json");
    }
    //Parts
    std::string path = "./Data/Parts/";

    if (std::is_same<T, Engine>::value) path += "Engines";
    else if (std::is_same<T, Tires>::value) path += "Tires";
    else if (std::is_same<T, AirIntake>::value) path += "AirIntakes";
    else if (std::is_same<T, Spoiler>::value) path += "Spoilers";
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
      try {
        T obj(data["collection"][i]);
        collection.emplace(dynamic_cast<Part&>(obj).getId(), obj);
      } catch (std::exception &e) {
        Menu::error("Corrupted data");
      }
    }
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