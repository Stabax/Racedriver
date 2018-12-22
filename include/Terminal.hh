#ifndef TERMINAL_HH_
#define TERMINAL_HH_

#include <string>
#include <memory>
#include <vector>
#include <ostream>
#include "Utils.hh"
#ifdef _WIN32
  #undef MOUSE_MOVED
  #include <pdcurses/curses.h>
#elif __linux__
  #include <curses.h>
#endif

class Terminal
{
public:
  enum Color {
    BlackOnWhite,
    WhiteOnBlack,
    RedOnBlack,
    BlackOnRed
  };

  Terminal();
  ~Terminal();

  static Terminal &get();


  void initColor();
  void clearScreen();
  void update();
  void setFullscreen();
  void setCanonical(bool set);
  void setStdinTimeout(int milliseconds);
  void resetAttrs();
  void setAttrs(int attrs);
  void print(const std::string &str, int attrs = 0, WINDOW *win = instance->_screen);
  void printAt(Point point, const std::string &str);
  WINDOW *addChildWindow(Point pos, Point size);
  void removeChildWindow(WINDOW *win);

  static std::unique_ptr<Terminal> instance;

  friend Terminal &operator<<(Terminal &term, const std::string str);
  friend Terminal &operator<<(Terminal &term, int data);
  friend Terminal &operator<<(Terminal &term, const char *str);

private:
  WINDOW *_screen;
  std::vector<WINDOW *> _windows;
  int _currentAttrs;
  int _rows;
  int _cols;
};

Terminal &operator<<(Terminal &term, const std::string str);
Terminal &operator<<(Terminal &term, int data);
Terminal &operator<<(Terminal &term, const char *str);
Terminal &operator<<(Terminal &dummy, Terminal &term);
Terminal &setColor(Terminal::Color color);
Terminal &setAttrs(int attrs);
Terminal &resetAttrs();

#endif /* !TERMINAL_HH_ */
