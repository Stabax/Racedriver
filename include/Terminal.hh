#ifndef TERMINAL_HH_
#define TERMINAL_HH_

#include <string>
#include <memory>
#include <vector>
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
  Terminal();
  ~Terminal();

  static Terminal &get();

  void clearScreen();
  void update();
  void setFullscreen();
  void setCanonical(bool set);
  void setStdinTimeout(int milliseconds);
  void print(const std::string &str);
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
  int _rows;
  int _cols;
};

#endif /* !TERMINAL_HH_ */
