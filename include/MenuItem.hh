#ifndef MENUITEM_HH_
#define MENUITEM_HH_

#include <memory>
#include <string>
#include "Terminal.hh"
#include "DataFile.hh"

/*!
 * @brief Holds menu entry data
 */
class MenuItem
{
public:
  enum Type {
    Button,
    Input
  };

  MenuItem(xml_node &data);

  static std::shared_ptr<MenuItem> create(xml_node &data);

  virtual void select() = 0;

protected:
  std::string _id;
  std::string _label;
};

/*!
 * @brief Acts as a button
 */
class MenuButton : public MenuItem
{
public:
  enum Type {
    Goto,
    Script
  };
  MenuButton(xml_node &data);

  virtual void select();

private:
  Type _type;
  std::string _target;
};

/*!
 * @brief Acts as a text input
 */
class MenuInput : public MenuItem
{
public:
  MenuInput(xml_node &data);

  virtual void select();
  std::string getData();

private:
  std::string _data;
};


#endif /* !MENUITEM_HH_ */