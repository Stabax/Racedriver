//fonctions.h
#ifndef fonctions_h
#define fonctions_h

#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include "sha/sha.h"

#define PWD_SALT	"RaceDriver"

inline void clrscreen()
{
  std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; //85 Retours
}

inline void videKBuffer()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

inline void msg(std::string message)
{
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
	std::cout << ":: " << message << "\n";
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n";
}

std::string getHashFromFile(std::string path);

inline void saisieInvalide()
{
	std::cout << ":::::::::::::::::::::::::::\n";
      std::cout << "::/!\\ Entree Invalide /!\\::\n";
	std::cout << ":::::::::::::::::::::::::::\n\n";
}

void error(std::string message); //le compilateur ne veut pas inliner: message peut être trop grand donc inefficace

#endif /* !FONCTIONS_HH_ */