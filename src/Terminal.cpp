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

std::unique_ptr<Terminal> Terminal::instance = nullptr;

Terminal::Terminal()
{
	_screen = initscr(); // Start Xcurses window
	setFullscreen();
	raw();
	keypad(_screen, TRUE);
	noecho();
	curs_set(2); //Block cursor
	initColor();
	resetAttrs();
	Terminal::instance = std::unique_ptr<Terminal>(this);
}

Terminal::~Terminal()
{
	endwin();	//Close Xcurses
}

Terminal &Terminal::get()
{
	return (*instance.get());
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
	for (size_t i = 0; i < _windows.size(); i++) //Update subwindows if exist
	{
		wrefresh(_windows[i]);
	}
}

void Terminal::setStdinTimeout(int milliseconds = -1)
{
	wtimeout(_screen, milliseconds);
}

void Terminal::resetAttrs()
{
	_currentAttrs = 0;
}

void Terminal::setAttrs(int attrs)
{
	_currentAttrs |= attrs;
}

void Terminal::print(const std::string &str, int attrs, WINDOW *win)
{
	if (attrs != 0) wattrset(win, attrs);
	waddstr(_screen, str.c_str());
	if (attrs != 0) wattroff(win, attrs);
	update();
}

void Terminal::printAt(Point point, const std::string &str)
{
	mvwaddstr(_screen, point.y, point.x, str.c_str());
	update();
}

WINDOW *Terminal::addChildWindow(Point pos, Point size)
{
	WINDOW *win = subwin(_screen, size.y, size.x, pos.y, pos.x);
	box(win, 0, 0);
	_windows.push_back(win);
	update();
  return (win);
}

void Terminal::removeChildWindow(WINDOW *win)
{
	auto it = std::find(_windows.begin(), _windows.end(), win);
	if (it == _windows.end()) throw std::runtime_error("Unknown window");
	_windows.erase(it);
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
  term.print(str, term._currentAttrs);
  return (term);
}

Terminal &operator<<(Terminal &dummy, Terminal &term)
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

