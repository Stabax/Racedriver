#include "Terminal.hh"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

Terminal::Terminal()
{
	_screen = initscr(); // Start Xcurses window
	setCanonical(true);
	mouse_set(ALL_MOUSE_EVENTS); //Enables mouse
	curs_set(2); //Block cursor
}

Terminal::~Terminal()
{
	endwin();	//Close Xcurses
}

void Terminal::test()
{
	*this << "toto sese la uic";
	sleep(2);
	clearScreen();
	printAt(Point(5, 5), "Hello World !!!");	/* Print Hello World */
	getch();
}

void Terminal::clearScreen()
{
  werase(_screen);
}

void Terminal::blit()
{
	refresh(); //Print all bufferized data
}

void Terminal::setCanonical(bool set = true)
{
  (set ? cbreak() : nocbreak());
}

void Terminal::setStdinTimeout(int milliseconds = -1)
{
	wtimeout(_screen, milliseconds);
}

Point Terminal::getMousePos()
{
	Point point;
  wmouse_position(_screen, &point.y, &point.x);
	return (point);
}

void Terminal::print(const std::string &str)
{
	waddstr(_screen, str.c_str());
	blit();
}

void Terminal::printAt(Point point, const std::string &str)
{
	mvwaddstr(_screen, point.y, point.x, str.c_str());
	blit();
}

WINDOW *Terminal::addChildWindow(Point pos, Point size)
{
  return (subwin(_screen, size.y, size.x, pos.y, pos.x));
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