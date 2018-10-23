#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#include <vector>

template <typename T>
class Collection
{
public:
  T &operator[](const std::string &key) {
    return (_collection[key]);
  }

  T &operator[](int id) {
    return (*_collection.begin() + id);
  }

private:
  std::map<std::string, T> _collection;
}

#endif /* !COLLECTION_HPP_ */