#include "DataFile.hh"

//JSON

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

//XML

MenuFile::MenuFile(const std::string &path)
 : _path(path)
{

}

bool MenuFile::load()
{
  std::ifstream file;

  file.open(_path, std::ifstream::in);
  if (!file.good()) return (false);
  //PARSE
  file.close();
  return (true);
}

bool MenuFile::save()
{
  return (save(_data));
}

bool MenuFile::save(const xml_node &data)
{
  std::ofstream file;

  file.open(_path, std::ofstream::out | std::ofstream::trunc);
  if (!file.good()) return (false);
  //DUMP
  file.close();
  return (true);
}

void MenuFile::setData(const xml_node &data)
{
  _data = data;
}

const xml_node &MenuFile::getData()
{
  return (_data);
}