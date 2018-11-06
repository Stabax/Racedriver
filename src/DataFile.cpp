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
  file.close();
  return (true);
}

bool DataFile::save()
{
  return (save(_data));
}

bool DataFile::save(const json &data)
{
  std::ofstream file;

  file.open(_path, std::ofstream::out | std::ofstream::trunc);
  if (!file.good()) return (false);
  file << data.dump();
  file.close();
  return (true);
}

void DataFile::setData(const json &data)
{
  _data = data;
}

const json &DataFile::getData()
{
  return (_data);
}