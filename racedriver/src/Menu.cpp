#include "Menu.hh"
#include <cstdio>
#include <cstdlib>
#include <pdcurses/curses.h>

Menu::Menu()
{

}

void Menu::initTerminal()
{
	initscr();			/* Start curses mode 		  */
	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
}

void Menu::clearScreen()
{
  
}