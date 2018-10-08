//fonctions.cpp
#include "fonctions.h"

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
	saveContent += PWD_SALT;
	lock = sha256(saveContent); //On inscrit le lock dans le fichier

	return lock;
}

void error(std::string message)
{
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
	std::cout << ":: ERREUR: " << message << "\n";
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n";
}