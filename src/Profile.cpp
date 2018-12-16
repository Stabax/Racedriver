//Profiles.cpp
#ifdef __GNUC__
#include <dirent.h>
#endif
#ifdef _MSC_VER
#include "dirent.h"
#endif
#include "Profile.hh"
#include "Menu.hh"

std::shared_ptr<Profile> Profile::active = nullptr;

Profile::Profile(const std::string &name)
 : name(name), difficulty(0), credits(10000), MenuModule("Profile"), garage()
{
	garage.addCar(Car::collection[0]);
}


Profile::Profile(const json &data)
 : name(data["name"].get<std::string>()), difficulty(data["difficulty"].get<int>()), credits(data["credits"].get<int>()), garage(data["garage"]), MenuModule("Profile")
{

}

Profile::~Profile()
{
}

void Profile::registerMethods()
{
	MenuModule::methods.emplace("save", [] () { Profile::active->save(); });
}

void Profile::create(const std::string &name)
{
	Profile::active = std::make_shared<Profile>(name);
}

void Profile::load(const std::string &name)
{
	DataFile save("./Data/Saves/"+name+".json");

	if (!save.load())
	{
		throw std::runtime_error("Cannot load profile:"+name);
	}
	Profile::active = std::make_shared<Profile>(save.getData());
}

void Profile::save()
{
	DataFile save("./Data/Saves/"+name+".json");
	json data = *this;

	if (!save.save(data))
	{
		Menu::error("Cannot save Profile: "+name);
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

std::vector<std::string> Profile::getSaves(std::string dir)
{
	std::vector<std::string> saves;
	DIR *dp;
	struct dirent *dirp;

	if ((dp = opendir(dir.c_str())) == NULL)
	{
			throw (std::runtime_error("Error opening " + dir));
	}
	while ((dirp = readdir(dp)) != NULL)
	{
		std::string file = std::string(dirp->d_name);
		size_t extpos = file.find(".json");
		if (extpos != std::string::npos)
		{
			saves.push_back(file.substr(0, extpos));
		}
	}
	closedir(dp);
	return (saves);
}


void Profile::displaySavesList()
{
	std::string path = "./Data/Saves/";
	std::vector<std::string> saves = getSaves(path);
	saves.insert(saves.begin(), ""); //Dummy to keep index true

	for (size_t i = 1; i < saves.size(); i++)
	{
		Terminal::get() << i << ". " << saves[i] << "\n";
	}
}

void Profile::supprimerProfile(const int& numeroSave)
{
	/*
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
	}*/
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

void to_json(json& j, const Profile& profile) {
	json garage = profile.garage;
	j = {
		{"name", profile.name},
		{"difficulty", profile.difficulty},
		{"credits", profile.credits},
		{"careerStats", {
			{"races", profile.careerStats.races},
			{"victories", profile.careerStats.victories},
			{"losses", profile.careerStats.losses},
			{"accidents", profile.careerStats.accidents},
			{"creditsEarned", profile.careerStats.creditsEarned},
			{"carBought", profile.careerStats.carBought}
		}},
		{"garage", garage}
	};
}
