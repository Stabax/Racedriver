#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#include <vector>

template <typename T>
class Collection
{
public:

  T &operator[](std::string name) {
    for (size_t i = 0; i < size(); i++)
    {
      if (_collection[i].name == name) return (i);
    }
  }

  T &operator[](int i) {
    return (_collection[i]);
  }

private:
  std::vector<T> _collection;
}

#endif /* !COLLECTION_HPP_ */