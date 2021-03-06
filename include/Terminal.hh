#ifndef TERMINAL_HH_
#define TERMINAL_HH_

#include <string>
#include <memory>
#include <map>
#include <ostream>
#include <functional>
#ifdef _WIN32
  #undef MOUSE_MOVED
  #include <pdcurses/curses.h>
#elif __linux__
  #include <curses.h>
#endif
#include <GraphicsRenderer.hh>

#define BASE_PAIR     1

class Terminal : public GraphicsRenderer
{
public:
  enum Color {
    //White bg
    BlackOnWhite,
    RedOnWhite,
    BlueOnWhite,
    YellowOnWhite,
    GreenOnWhite,
    MagentaOnWhite,
    CyanOnWhite,
    //Black bg
    WhiteOnBlack,
    RedOnBlack,
    BlueOnBlack,
    YellowOnBlack,
    GreenOnBlack,
    MagentaOnBlack,
    CyanOnBlack,
    //Custom
    BlackOnRed
  };

  Terminal(WINDOW *win);
  virtual ~Terminal();

  static void start();
  static void initColor();
  static void close();

  void setFullscreen();
  void setCursor(int style);

  Point getCursorPos();
  void setCursorPos(const Point &p);

  void resetAttrs();
  void setAttrs(int attrs);
  void print(const std::string &str, int attrs = 0);
  void printAt(Point point, const std::string &str, int attrs = 0);

  void clearScreen();
  void update();

  //Renderer impl
  virtual void clear();
  virtual void draw(const std::string &str, int x, int y);
  virtual void setColor(GraphicsRenderer::Color color);

  Terminal &addWindow(const std::string &winId, Point pos, Point size);
  static void removeWindow(const std::string &winId);

  static std::map<std::string, Terminal> windows; //Public window map

  Terminal &operator<<(std::function<Terminal&(Terminal &term)>);
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

#endif /* !TERMINAL_HH_ */
