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

  void test();
  void clearScreen();
  void blit();
  void setCanonical(bool set);
  void setStdinTimeout(int milliseconds);
  Point getMousePos();
private:
  WINDOW *_screen;
};

#endif /* !TERMINAL_HH_ */