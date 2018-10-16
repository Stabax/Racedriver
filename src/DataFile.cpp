#include "DataFile.hh"

DataFile::DataFile(const char *path)
 : _path(path)
{

}

bool DataFile::load()
{
  std::ifstream file(_path, std::ifstream::in);

  if (!file.good())
  {
    return (false);
  }
  while (file.good()) file >> _data;
  return (true);
}

bool DataFile::save()
{
  return (true);
}