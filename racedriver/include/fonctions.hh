//fonctions.h
#ifndef fonctions_h
#define fonctions_h

#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <pdcurses/curses.h>
#include "Menu.hh"
#include "sha/sha.h"

#define PWD_SALT	"RaceDriver"
/* historic videKBuffer relic
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
*/

std::string getHashFromFile(std::string path);

inline void saisieInvalide()
{
  Menu::msg("/!\\ Entree Invalide /!\\");
}

inline std::string getString()
{
	char str[256];
	getnstr(str, 255);
	return (std::string(str));
}

#endif /* !FONCTIONS_HH_ */