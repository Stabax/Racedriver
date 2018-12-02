#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#include <vector>
#include "DataFile.hh"
#include "Menu.hh"
#include "Part.hpp"

//Forward declaring parts
class Car;
class Engine;
class Tires;
class AirIntake;
class Spoiler;

/*!
 * @brief Dummy Collection declaration to allow SFINAE specification
 */
template <typename T, typename enable = void>
class Collection;

/*!
 * @brief SFINAE helper to prevent specialization of Collection to a class that is not based on Part.
 */
//template<typename T>
//using EnableIfPolicy = ;

/*!
 * @brief "Container" for any class with a based on Part.
 */
template <typename T>
class Collection<T, typename std::enable_if_t<std::is_base_of<Part, T>::value>>
{
public:
  void push(T obj)
  {
    _collection.push_back(obj);
  }

  size_t size() const
  {
    return (_collection.size());
  }

  T &operator[](const std::string &key) {
    for (size_t i = 0; i < _collection.size(); i++)
    {
      if (dynamic_cast<Part&>(_collection[i]).getId() == key) return (_collection[i]);
    }
    throw std::runtime_error("Uknown part");
  }

  T &operator[](int index) {
    return (_collection[index]);
  }

  template <typename ST>
  static const std::string getPath()
  {
    std::string path = "./Data/";
    if (std::is_same<ST, Car>::value)
    {
      path += "Cars";
    }
    else //Parts
    {
     path += "Parts/" + ST::getPath();
    }
    /*
    if (std::is_same<ST, Engine>::value) path += "Engines";
    else if (std::is_same<ST, Tires>::value) path += "Tires";
    else if (std::is_same<ST, AirIntake>::value) path += "AirIntakes";
    else if (std::is_same<ST, Spoiler>::value) path += "Spoilers";
    else throw std::runtime_error("Unknown part type");*/
    return (path+".json");
  }

  template <typename ST>
  static void load(Collection<ST> &collection)
  {
    std::string path;
    try {
      path = getPath<ST>();
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
        ST obj(data["collection"][i]);
        collection.push(obj);
      } catch (std::exception &e) {
        Menu::error("Corrupted data");
      }
    }
  }

private:
  std::vector<T> _collection;
};

#endif /* !COLLECTION_HPP_ */