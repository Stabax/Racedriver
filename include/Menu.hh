#ifndef MENU_HH_
#define MENU_HH_

#include <string>
#include <vector>
#include <deque>
#include <map>
#include <memory>
#include <functional>
#include "DataFile.hh"
#include "MenuItem.hh"

/*!
 * @brief Base/Generic class for Menu
 */
class Menu
{
public:
  //Generic
  static void printASCIILogo(int art);
  static void alert(std::string str);
  static void msg(std::string str);
  static void error(std::string str);

  static bool askConfirmation();
  static int askChoice();

  static void setActiveDocument(const std::string &source, const DataSource sourceMode);
  static void setActiveDocument(std::shared_ptr<MenuFile> doc);

  static void goTo(std::string id, std::string source = "", DataSource sourceMode = DataSource::Filesystem);
  static void popUp(std::string id, std::string source = "", DataSource sourceMode = DataSource::Filesystem);
  static bool run();

  static std::shared_ptr<Menu> active;
  static std::shared_ptr<MenuFile> activeDoc;

  //Instance
  Menu(const std::string &id);

  void onLoad();

  void addAlert(std::shared_ptr<MenuItem> menuItem);
  std::shared_ptr<MenuItem> getItem(const std::string &id);
  void setClickCallback(std::function<void()> callback);

  void updateCursor(bool add);
  bool update();
  void render();
  void renderConsole(std::string command);

private:
  std::string _id;
  std::deque<std::shared_ptr<MenuItem>> _alerts;
  std::vector<std::shared_ptr<MenuItem>> _entities;
  std::vector<std::shared_ptr<MenuItem>> _items;
  std::string _onLoadScript;
  std::shared_ptr<std::function<void()>> _clickCallback;
  int _lastInput;
  int _title; //title art
  int _cursor;
};

/*!
 * @brief Acts as a sub window
 */
class MenuDialog
{
public:
  MenuDialog(xml_node &data);

  static void load(const xml_document &doc);

  static std::map<std::string, MenuDialog> dialogs;

  void open();
  void render();

private:
  std::string _data;
  WINDOW *_win;
};

std::string getHashFromFile(std::string path);
std::string getString();

#endif /* !MENU_HH_ */