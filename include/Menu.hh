#ifndef MENU_HH_
#define MENU_HH_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include "DataFile.hh"

#define INVOKE_SEPARATOR  "::"

/*!
 * @brief Holds menu entry data
 */
struct MenuItem {
  MenuItem(xml_node &data);

  void OnClick();
};

/*!
 * @brief Inherited by classes that need to be callable from script
 */
struct MenuModule
{
  MenuModule(const std::string &id);
  virtual void registerMethods() = 0;

  std::map<std::string, std::function<void()>> methods;
};

/*!
 * @brief Base/Generic class for Menu
 */
class Menu
{
public:
  //Generic
  static void msg(std::string str);
  static void error(std::string str);

  static bool askConfirmation();
  static int askChoice();

  static bool invokeMethod(const std::string &methodId);

  static std::map<std::string, std::shared_ptr<MenuModule>> modules;

  //Instance
  Menu(const std::string &path);

private:
  std::vector<MenuItem> _items;
};

std::string getHashFromFile(std::string path);
std::string getString();

#endif /* !MENU_HH_ */