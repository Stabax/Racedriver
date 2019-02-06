#include "Terminal.hh"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#ifdef __GNUC__
#include <unistd.h>
#endif
#ifdef _MSC_VER
#include <windows.h>
#endif

std::map<std::string, Terminal> Terminal::windows;
std::unique_ptr<Terminal> Terminal::instance = nullptr;

Terminal::Terminal()
{
	_screen = initscr(); // Start Xcurses window
	setFullscreen();
	raw();
	keypad(_screen, TRUE);
	noecho();
	setCursor(0); //No cursor
	initColor();
	resetAttrs();
	if (instance != nullptr) throw (std::runtime_error("Cannot reinstanciate singleton"));
	Terminal::instance = std::unique_ptr<Terminal>(this);
}

Terminal::Terminal(WINDOW *win)
{
	_screen = win;
}

Terminal::~Terminal()
{
	endwin();	//Close Xcurses
}

Terminal &Terminal::get()
{
	return (*instance.get());
}

Point Terminal::getCursorPos()
{
	Point p;
	getyx(_screen, p.y, p.x);
	return (p);
}

void Terminal::setCursorPos(const Point &p)
{
	wmove(_screen, p.y, p.x);
}

void Terminal::initColor()
{
  if (!has_colors()) throw (std::runtime_error("Color is not supported"));
	start_color();
	init_pair(Color::BlackOnWhite, COLOR_BLACK, COLOR_WHITE);
	init_pair(Color::WhiteOnBlack, COLOR_WHITE, COLOR_BLACK);
	init_pair(Color::RedOnBlack, COLOR_RED, COLOR_BLACK);
	init_pair(Color::BlackOnRed, COLOR_BLACK, COLOR_RED);
}

void Terminal::setFullscreen()
{
	resize_term(2000, 2000);
	getmaxyx(_screen, _rows, _cols); // Get the largest physical screen dimensions
	_rows *= 0.75f;
	_cols *= 0.75f;
	resize_term(_rows, _cols);
}

void Terminal::clearScreen()
{
  wclear(_screen);
}

void Terminal::update()
{
	refresh(); //Print all bufferized data
}

void Terminal::setStdinTimeout(int milliseconds = -1)
{
	wtimeout(_screen, milliseconds);
}

void Terminal::setCursor(int style)
{
	curs_set(style);
}

void Terminal::resetAttrs()
{
	_currentAttrs = 0;
}

void Terminal::setAttrs(int attrs)
{
	_currentAttrs |= attrs;
}

void Terminal::print(const std::string &str, int attrs)
{
	print(_screen, str, attrs);
}

void Terminal::print(WINDOW *win, const std::string &str, int attrs)
{
	if (attrs != 0 || _currentAttrs != 0) wattrset(win, attrs + _currentAttrs);
	waddstr(win, str.c_str());
	if (attrs != 0 || _currentAttrs != 0) wattroff(win, attrs + _currentAttrs);
	update();
}

void Terminal::printAt(Point point, const std::string &str)
{
	mvwaddstr(_screen, point.y, point.x, str.c_str());
	update();
}

Terminal &Terminal::addChildWindow(const std::string &winId, Point pos, Point size)
{
	WINDOW *win = subwin(_screen, size.y, size.x, pos.y, pos.x);
	box(win, 0, 0);
	windows.emplace(winId, Terminal(win));
	update();
  return (windows[winId]);
}

void Terminal::removeChildWindow(const std::string &winId)
{
	auto it = windows.find(winId);
	if (it == windows.end()) throw std::runtime_error("Unknown window");
	windows.erase(it);
}

//I/O Streaming

Terminal &operator<<(Terminal &term, const std::string str)
{
  return (term << str.c_str());
}

Terminal &operator<<(Terminal &term, int data)
{
  return (term << std::to_string(data));
}

Terminal &operator<<(Terminal &term, const char *str)
{
  term.print(str);
  return (term);
}

Terminal &operator<<([[maybe_unused]]Terminal &dummy, Terminal &term)
{
	return (term);
}

Terminal &setColor(Terminal::Color color)
{
	Terminal::get().setAttrs(COLOR_PAIR(static_cast<int>(color)));
  return (Terminal::get());
}

Terminal &setAttrs(int attrs)
{
	Terminal::get().setAttrs(attrs);
  return (Terminal::get());
}

Terminal &resetAttrs()
{
	Terminal::get().resetAttrs();
  return (Terminal::get());
}

