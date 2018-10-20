//AirIntake.cpp
#include "AirIntake.hh"
#include "Menu.hh"

std::vector<AirIntake> AirIntake::collection = std::vector<AirIntake>();

AirIntake::AirIntake(const std::string& modele, const char& rang, const int& aerodynamisme)
 : Part(), _name(modele), _rank(rang), _aerodynamic(aerodynamisme)
{
}

AirIntake::AirIntake(const json &data)
 : Part(), _name(data["name"].get<std::string>()), _rank(data["rank"].get<std::string>()[0]), _aerodynamic(data["aerodynamic"].get<int>()), _price(vRang(_rank) * 1500)
{
}

AirIntake::~AirIntake()
{

}

AirIntake* AirIntake::chargerAirIntake(const int& id)
{
	AirIntake* AirIntakeCharge = 0; //AirIntake a creer
	std::string var=""; //contient les lignes du fichier
	std::string chemin = "Data/composants/priseair.cdx";
	int idActuel = id + 1; //indique l'id actuellement lu dans le fichier

	std::ifstream engine(chemin.c_str());

	if(!engine)
	{
		Menu::error("Echec de lecture du fichier priseair.cdx");
	}
	else
	{
		while(idActuel!=id && std::getline(engine, var))
		{
			std::istringstream iss(var.substr(0,var.find_first_of(";"))); //on transforme le premier char en int pour etre compare
			if(iss>>idActuel)
			{
			}
			else
			{
				Menu::error("Fichier corrompu12");
			}
			//on utilise while(std::getline(flux, string) pour "Tant qu'il y a une ligne a lire"
		}

		if(idActuel==id)
		{
			int curseur;
			var.erase(0,var.find_first_of(";")+1);

			curseur=var.find_first_of(";");
			std::string modele=var.substr(0,curseur);
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			char rang=var[0];
			var.erase(0,curseur+1);

			std::string sAerodynamisme=var;

			int aerodynamisme;

			std::istringstream iss;
			iss.str(sAerodynamisme);
			if (iss>>aerodynamisme)
			{
			}
			else
			{
				Menu::error("Fichier corompu14.");
			}

			AirIntakeCharge = new AirIntake(modele, rang, aerodynamisme);
		}
		else
		{
			Menu::error("Fichier corompu15.");
		}
	}
	return AirIntakeCharge;
}

void AirIntake::infoAirIntake(const int& id, int& prix)
{
	std::string var = ""; //contient les lignes du fichier
	std::string chemin ="Data/composants/priseair.cdx";
	std::ifstream engine(chemin.c_str());
	std::istringstream iss;
	int idActuel = 0; //indique l'id actuellement lu dans le fichier
	int curseur;
	char rang;

	if(!engine)
	{
		Menu::error("Echec de lecture du fichier priseair.cdx");
	}
	else
	{
		while(idActuel!=id && std::getline(engine, var))
		{
			iss.str(var.substr(0,var.find_first_of(";"))); //on transforme le premier char en int pour etre compare
			if(iss>>idActuel)
			{
			}
			else
			{
				Menu::error("Fichier corrompu18b");
			}
			iss.clear();
		}
		curseur = var.find_first_of(";");
		var.erase(0, curseur + 1); // On retire l'id
		if(idActuel==id)
		{
			curseur = var.find_first_of(";");
			var.erase(0, curseur + 1);

			rang = var[0];

			prix =  vRang(rang) * 300 + id * 100;
		}
		else
		{
			Menu::error("Fichier corompu21b.");
		}
	}
}

void AirIntake::infoAirIntake(const int& id, std::string& modele, char& rang, int& aero, int& prix)
{
	std::string var = ""; //contient les lignes du fichier
	std::string chemin ="Data/composants/priseair.cdx";
	std::ifstream engine(chemin.c_str());
	std::istringstream iss;
	int idActuel = 0; //indique l'id actuellement lu dans le fichier
	int curseur;

	if(!engine)
	{
		Menu::error("Echec de lecture du fichier priseair.cdx");
	}
	else
	{
		while(idActuel!=id && std::getline(engine, var))
		{
			iss.str(var.substr(0,var.find_first_of(";"))); //on transforme le premier char en int pour etre compare
			if(iss>>idActuel)
			{
			}
			else
			{
				Menu::error("Fichier corrompu18b");
			}
			iss.clear();
		}
		curseur = var.find_first_of(";");
		var.erase(0, curseur + 1); // On retire l'id
		if(idActuel==id)
		{
			curseur = var.find_first_of(";");
			modele=var.substr(0,curseur);
			var.erase(0, curseur + 1);

			curseur = var.find_first_of(";");
			rang=var[0];
			var.erase(0, curseur + 1);

			std::string sAero=var.substr(0,curseur);

			iss.clear();
			iss.str(sAero);
			if(iss >> aero)
			{
			}
			else
			{
				Menu::error("Fichier corrompu ta mere");
			}

			prix =  vRang(rang) * 300 + id * 100;

		}
		else
		{
			Menu::error("Fichier corompu21b.");
		}
	}
}

std::string AirIntake::getName() const
{
	return (_name);
}

char AirIntake::getRank() const
{
	return (_rank);
}

int AirIntake::getAerodynamic() const
{
	return (_aerodynamic);
}

int AirIntake::getPrice() const
{
	return _price;
}