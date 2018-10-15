#include "DataFile.hh"

DataFile::DataFile(const char *path)
 : _path(path)
{

}

bool DataFile::Load()
{
  std::ifstream file(_path, std::ifstream::in);

  if (!file.good())
  {
    throw ("Error opening DataFile");
    return (false);
  }
  while (file.good()) file >> _data;
  return (true);
}

bool DataFile::Save()
{
  return (true);
}