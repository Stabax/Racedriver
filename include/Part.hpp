#ifndef PART_HPP_
#define PART_HPP_

#include <vector>
#include "DataFile.hh"

//Forward declaring parts
class Tires;
class AirIntake;
class Spoiler;

class Part
{
public:
  Part()
  {
  }

  virtual ~Part()
  {
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
  static void loadCollection(std::vector<T> &collection)
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
    collectionFile.copyTo(collection);
  }

private:
};

#endif /* !PART_HPP_ */