#ifndef TERMINAL_HH_
#define TERMINAL_HH_

#include <string>
#include <memory>
#include <map>
#include <ostream>
#include "Utils.hh"
#ifdef _WIN32
  #undef MOUSE_MOVED
  #include <pdcurses/curses.h>
#elif __linux__
  #include <curses.h>
#endif

#define BASE_PAIR     1

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
  Terminal(WINDOW *win);
  ~Terminal();

  static Terminal &get();

  void initColor();
  void setFullscreen();
  void setStdinTimeout(int milliseconds);
  void setCursor(int style);

  Point getCursorPos();
  void setCursorPos(const Point &p);

  void resetAttrs();
  void setAttrs(int attrs);
  void print(const std::string &str, int attrs = 0);
  void print(WINDOW *win, const std::string &str, int attrs = 0);
  void printAt(Point point, const std::string &str);

  void clearScreen();
  void update();

  Terminal &addChildWindow(const std::string &winId, Point pos, Point size);
  void removeChildWindow(const std::string &winId);

  static std::unique_ptr<Terminal> instance;

  static std::map<std::string, Terminal> windows; //Public window map

  friend Terminal &operator<<(Terminal &term, const std::string str);
  friend Terminal &operator<<(Terminal &term, int data);
  friend Terminal &operator<<(Terminal &term, const char *str);

private:
  WINDOW *_screen;
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
