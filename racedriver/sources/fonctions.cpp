
//fonctions.cpp

#ifndef algos_h
#define algos_h

#include "fonctions.h"

std::string getSalt()
{
	return "racedriver";
}

std::string getHashFromFile(std::string path)
{
	std::ifstream file(path.c_str()); //flux de lecture de la sauvegarde

	std::string ligneChargee;
	std::string saveContent;
	std::string lock;

	while(getline(file, ligneChargee))
	{
		saveContent += ligneChargee; //On remplit le string qui contient la sauvegarde
	}
	saveContent += getSalt();
	lock = sha256(saveContent); //On inscrit le lock dans le fichier

	return lock;
}

//le compilateur ne veut pas inliner: message peut être trop grand donc inefficace
void error(std::string message)
{
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
	std::cout << ":: ERREUR: " << message << "\n";
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n";
}

#endif






