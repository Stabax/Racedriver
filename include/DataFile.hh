#ifndef DATAFILE_HH_
#define DATAFILE_HH_

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class DataFile
{
public:
  DataFile(const char *path);

  bool Load();
  bool Save();

private:
  const char *_path;
  json _data;
};

#endif /* !DATAFILE_HH_ */