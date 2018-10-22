#ifndef DATAFILE_HH_
#define DATAFILE_HH_

#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


class DataFile
{
public:
  DataFile(const std::string &path);

  bool load();
  bool save();

  const json &getData();

private:
  const std::string _path;
  json _data;
};

#endif /* !DATAFILE_HH_ */