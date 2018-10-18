#ifndef DATAFILE_HH_
#define DATAFILE_HH_

#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class DataFile
{
public:
  DataFile(const char *path);

  bool load();
  bool save();

  template <typename T>
  void copyTo(std::vector<T> &collection)
  {
    for (size_t i = 0; i < _data["collection"].size(); i++)
    {
      collection.push_back(T(_data["collection"][i]));
    }
  }

private:
  const char *_path;
  json _data;
};

#endif /* !DATAFILE_HH_ */