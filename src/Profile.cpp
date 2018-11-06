//Profiles.cpp
#include "Profile.hh"
#include "Menu.hh"

std::shared_ptr<Profile> Profile::active = nullptr;

Profile::Profile(const std::string &name)
 : name(name), difficulty(0), credits(10000), garage()
{

}


Profile::Profile(const json &data)
 : name(data["name"].get<std::string>()), difficulty(data["difficulty"].get<int>()), credits(data["credits"].get<int>()), garage(data["garage"])
{

}

Profile::~Profile()
{
}

void Profile::create(const std::string &name)
{
	Profile::active = std::make_shared<Profile>(name);
}

void Profile::load(const std::string &name)
{
	DataFile save("./Saves/"+name+".json");

	if (!save.load())
	{
		throw std::runtime_error("Cannot load collection file:"+name);
	}
	Profile::active = std::make_shared<Profile>(save.getData());
}

void Profile::save()
{
	DataFile save("./Saves/"+name+".json");

	if (!save.save())
	{
		throw std::runtime_error("Cannot save Profile: "+name);
	}
}

bool Profile::compatible(Profile& Player, const int& numeroBox, const char& rangNewPiece)
{
	bool compatible = false;
	int rangPiece = 0;
	int rangCarBox = 0;
	//Car *CarBox = Player.getBox(numeroBox);

	//rangCarBox = vRang(CarBox->rank);
	rangPiece = vRang(rangNewPiece);

	if(rangCarBox <= rangPiece)
	{
		compatible = true;
	}
	else
	{
		compatible = false;
	}
	return compatible;
}

void Profile::listerSauvegardes()
{
	int i = 1;
	std::string numeroSave;    // string which will contain the result
	std::string nomProfile;
	std::ostringstream oss;   // stream utilise pour la conversion
	bool ouvert = true;
	do
	{
		oss.str(""); //On vide le contenu de oss
		oss << i;      // on insere le int dans le stream oss
		numeroSave = oss.str(); // range le int dans la variable numeroSave
		std::ifstream fichier( "Saves/Profile" + numeroSave + ".save" );

		if(fichier)
		{
			for (size_t ligne = 1; ligne <= 2; ligne++) //le nom est stocké sur la deuxieme ligne
			{
				getline(fichier, nomProfile);
			}
			Terminal::get() << i << ". Profile " << i << ": " << nomProfile << "\n";
			i++; // on incremente
		}
		else
		{
			ouvert = false;
		}
	}while(ouvert);
	Terminal::get() << "\n"; // on separe le bloc de Profiles du choix annuler
}

int Profile::compterSauvegardes()
{
	int i = 1;
	std::string numeroSave;          // string which will contain the result
	std::ostringstream oss;   // stream utilise pour la conversion
	bool ouvert = true;

	do
	{
		oss.str(""); //On vide le contenu de oss
		oss << i;      // on insere le int dans le stream oss
		numeroSave = oss.str(); // range le int dans la variable numeroSave
 		std::ifstream fichier("Saves/Profile" + numeroSave + ".save");

		if(fichier)
		{
			i++; // on incremente
		}
		else
		{
			ouvert = false;
		}
	}while(ouvert);
	return i - 1; //Un tour de test supplementaire est fait, d'ou le -1
}

void Profile::supprimerProfile(const int& numeroSave)
{
	bool test;
	bool fail = false;
	std::string numeroProfile;
	std::string numeroNewProfile;
	std::ostringstream oss;   // stream utilise pour la conversion
	std::string cheminFichier;
	std::string newCheminFichier;
	std::string cheminLock;
	std::string newCheminLock;
	int nbSaves = compterSauvegardes();

	oss << numeroSave;      // on insere le int dans le stream oss
	numeroProfile = oss.str(); // range le int dans la variable numeroSave
	cheminFichier = "Saves/Profile" + numeroProfile + ".save";
	cheminLock = "Saves/Profile" + numeroProfile + ".lock";
	if(remove(cheminFichier.c_str()))
	{
		Terminal::get().clearScreen();
		Menu::error("Impossible de supprimer le Profile");
		fail = true;
	}
	if(remove(cheminLock.c_str()))
	{
		Terminal::get().clearScreen();
		Menu::error("Impossible de supprimer le verrou du Profile");
		fail = true;
	}
	if(nbSaves > numeroSave)
	{
		for (int i = numeroSave; i < nbSaves; i++)
		{
			oss.str("");
			oss << i;      // on insere le int dans le stream oss
			numeroNewProfile = oss.str(); // range le int dans la variable numeroProfile
			newCheminFichier = "Saves/Profile" + numeroNewProfile + ".save";
			newCheminLock = "Saves/Profile" + numeroNewProfile + ".lock";

			oss.str("");
			oss << i + 1;
			numeroNewProfile = oss.str();
			cheminFichier = "Saves/Profile" + numeroNewProfile + ".save";
			cheminLock = "Saves/Profile" + numeroNewProfile + ".lock";

			test = rename(cheminFichier.c_str(), newCheminFichier.c_str()); //On decale toutes les saves d'un cran
			if(test == 1)
			{
				Terminal::get().clearScreen();
				Menu::error("Impossible de renommer les Profiles suivants.");
				fail = true;
			}
			test = rename(cheminLock.c_str(), newCheminLock.c_str()); //On decale tous les locks d'un cran
			if(test == 1)
			{
				Terminal::get().clearScreen();
				Menu::error("Impossible de renommer les verrous des Profiles suivants.");
				fail = true;
			}
		}
	}
	if(fail == false)
	{
		Terminal::get().clearScreen();
		Menu::msg("Profile"+numeroProfile+" supprime avec succes !");
	}
}

bool Profile::payer(const int& prix)
{
	bool paye;
	if(prix > credits)
	{
		Menu::error("Vous ne disposez pas d'assez de Credits !");
		paye = false;
	}
	else
	{
		credits -= prix;
		paye = true;
	}
	return paye;
}