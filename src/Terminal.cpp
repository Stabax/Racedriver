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

Terminal::Terminal(WINDOW *win)
 : GraphicsRenderer(0, 0), _currentAttrs(0)
{
	_screen = win;
}

Terminal::~Terminal()
{
}

void Terminal::start()
{
	if (windows.find("main") != windows.end()) throw (std::runtime_error("Cannot reinstanciate main term"));
	windows.emplace("main", Terminal(initscr())); // Start Xcurses window
	//Global init
	raw();
	initColor();
	noecho();
	//Instance init
	Terminal &main = windows.at("main");
	main.setFullscreen();
	main.setCursor(0); //No cursor
	keypad(main._screen, TRUE);
}

void Terminal::initColor()
{
  if (!has_colors()) throw (std::runtime_error("Color is not supported"));
	start_color();
	//White bg
	init_pair(Color::BlackOnWhite, COLOR_BLACK, COLOR_WHITE);
	init_pair(Color::RedOnWhite, COLOR_RED, COLOR_BLACK);
	init_pair(Color::BlueOnWhite, COLOR_BLUE, COLOR_BLACK);
	init_pair(Color::YellowOnWhite, COLOR_YELLOW, COLOR_BLACK);
	init_pair(Color::GreenOnWhite, COLOR_GREEN, COLOR_BLACK);
	init_pair(Color::MagentaOnWhite, COLOR_YELLOW, COLOR_BLACK);
	init_pair(Color::CyanOnWhite, COLOR_GREEN, COLOR_BLACK);
	//Black bg
	init_pair(Color::WhiteOnBlack, COLOR_WHITE, COLOR_BLACK);
	init_pair(Color::RedOnBlack, COLOR_RED, COLOR_BLACK);
	init_pair(Color::BlueOnBlack, COLOR_BLUE, COLOR_BLACK);
	init_pair(Color::YellowOnBlack, COLOR_YELLOW, COLOR_BLACK);
	init_pair(Color::GreenOnBlack, COLOR_GREEN, COLOR_BLACK);
	init_pair(Color::MagentaOnBlack, COLOR_YELLOW, COLOR_BLACK);
	init_pair(Color::CyanOnBlack, COLOR_GREEN, COLOR_BLACK);
	//Custom
	init_pair(Color::BlackOnRed, COLOR_BLACK, COLOR_RED);
}

void Terminal::close()
{
	windows.clear();
	endwin();	//Close Xcurses
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
	wrefresh(_screen); //Print all bufferized data
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
	if (attrs != 0 || _currentAttrs != 0) wattrset(_screen, attrs + _currentAttrs);
	waddstr(_screen, str.c_str());
	if (attrs != 0 || _currentAttrs != 0) wattroff(_screen, attrs + _currentAttrs);
	update();
}

void Terminal::printAt(Point point, const std::string &str, int attrs)
{
	if (attrs != 0 || _currentAttrs != 0) wattrset(_screen, attrs + _currentAttrs);
	mvwaddstr(_screen, point.y, point.x, str.c_str());
	if (attrs != 0 || _currentAttrs != 0) wattroff(_screen, attrs + _currentAttrs);
	update();
}

Terminal &Terminal::addWindow(const std::string &winId, Point pos, Point size)
{
	windows.emplace(winId, Terminal(subwin(_screen, size.y, size.x, pos.y, pos.x)));
	return (windows.at(winId));
}

void Terminal::removeWindow(const std::string &winId)
{
	auto it = windows.find(winId);
	if (it == windows.end()) throw std::runtime_error("Unknown window");
	windows.erase(it);
}

// Renderer

void Terminal::clear()
{
	Terminal::clearScreen();
}

void Terminal::draw(const std::string &str, int x, int y)
{
	printAt(Point(x, y), str);
}

void Terminal::setColor(GraphicsRenderer::Color color)
{
	setAttrs(COLOR_PAIR(static_cast<int>(color)));
}

Terminal &Terminal::operator<<(std::function<Terminal &(Terminal &term)> f)
{
	return (f(*this));
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
