#include "DataFile.hh"
#ifdef __GNUC__
#include <dirent.h>
#endif
#ifdef _MSC_VER
#include "dirent.h"
#endif

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


std::vector<std::string> DataFile::getFolderContents(std::string path, std::string filter, bool truncateFilter)
{
	std::vector<std::string> files;
	DIR *dp;
	struct dirent *dirp;

	if ((dp = opendir(path.c_str())) == NULL)
	{
			throw (std::runtime_error("Error opening " + path));
	}
	while ((dirp = readdir(dp)) != NULL)
	{
		std::string file = std::string(dirp->d_name);
    if (filter == "" || file.find(filter) != std::string::npos)
    {
      if (truncateFilter) files.push_back(file.substr(0, file.find(filter)));
      else files.push_back(file);
    }
	}
	closedir(dp);
	return (files);
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