#ifndef DATAFILE_HH_
#define DATAFILE_HH_

#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <pugixml.hpp>
using xml_node = pugi::xml_node;

/*!
 * @brief JSON File I/O serialization class
 */
class DataFile
{
public:
  DataFile(const std::string &path);

  bool load();
  bool save();
  bool save(const json &data);

  void setData(const json &data);
  const json &getData();

private:
  const std::string _path;
  json _data;
};

/*!
 * @brief XML File I/O serialization class
 */
class MenuFile
{
public:
  MenuFile(const std::string &path);

  bool load();
  bool save();
  bool save(const xml_node &data);

  void setData(const xml_node &data);
  const xml_node &getData();

private:
  const std::string _path;
  xml_node _data;
};

#endif /* !DATAFILE_HH_ */