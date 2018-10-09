#include "Terminal.hh"
#include <cstdio>
#include <cstdlib>

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
	mvprintw(5, 5, "Hello World !!!");	/* Print Hello World		  */
	blit();
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

