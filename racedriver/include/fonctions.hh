//fonctions.h
#ifndef fonctions_h
#define fonctions_h

#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <pdcurses/curses.h>
#include "sha/sha.h"

#define PWD_SALT	"RaceDriver"
/* historic videKBuffer relic
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
*/

inline void msg(std::string message)
{
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
	std::cout << ":: " << message << "\n";
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n";
}

std::string getHashFromFile(std::string path);

inline void saisieInvalide()
{
  msg("/!\\ Entree Invalide /!\\");
}

inline std::string getString()
{
	char str[256];
	getnstr(str, 255);
	return (std::string(str));
}

void error(std::string message); //le compilateur ne veut pas inliner: message peut être trop grand donc inefficace

#endif /* !FONCTIONS_HH_ */