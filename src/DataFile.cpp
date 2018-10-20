#include "DataFile.hh"

DataFile::DataFile(const std::string &path)
 : _path(path)
{

}

bool DataFile::load()
{
  std::ifstream file;

  file.open(_path, std::ifstream::in);
  if (!file.good()) return (false);
  _data = json::parse(file);
  return (true);
}

bool DataFile::save()
{
  return (true);
}