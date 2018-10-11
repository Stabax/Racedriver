#ifndef TERMINAL_HH_
#define TERMINAL_HH_

#include <memory>
#include <pdcurses/curses.h>
#include "Utils.hpp"

class Terminal
{
public:
  Terminal();
  ~Terminal();

  static Terminal &get();

  void clearScreen();
  void blit();
  void setFullscreen();
  void setCanonical(bool set);
  void setStdinTimeout(int milliseconds);
  Point getMousePos();
  void print(const std::string &str);
  void printAt(Point point, const std::string &str);
  WINDOW *addChildWindow(Point pos, Point size);

  static std::unique_ptr<Terminal> instance;

  friend Terminal &operator<<(Terminal &term, const std::string str);
  friend Terminal &operator<<(Terminal &term, int data);
  friend Terminal &operator<<(Terminal &term, const char *str);

private:
  WINDOW *_screen;
  int _rows;
  int _cols;
};

#endif /* !TERMINAL_HH_ */