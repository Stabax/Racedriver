//Car.cpp
#include "Car.hh"
#include "Menu.hh"

std::map<std::string, Car> Car::collection = std::map<std::string, Car>();

Car::Car(const json &data)
 : Part(data), _engine(Engine::collection[idEngine]), _spoiler(Spoiler::collection[idSpoiler]), _airIntake(AirIntake::collection[idAirIntake]),
   _tires(Tires::collection[idTires]), _nitro(nitroMax), manufacturer(marque), _model(modele), rank(rang), _nitroMax(nitroMax), _durability(etat)
{

}

Car::~Car()
{
}

Car* Car::chargerCar(const int& id, const char& rangCharge)
{
	Car* CarCharge = 0; //moteur a creer
	std::string var=""; //contient les lignes du fichier
	std::string sRang;
	sRang = rangCharge;
	std::string chemin = "Data/Cars/"+sRang+".cdx";
	std::ifstream engine(chemin.c_str());
	std::istringstream iss;

	if(!engine)
	{
		Menu::error("Echec de lecture du fichier "+sRang+".cdx");
	}
	else
	{
		int idActuel = id + 1; //indique l'id actuellement lu dans le fichier
		while(idActuel!=id && std::getline(engine, var)) //on lit dans le fichier
		{
			//on utilise while(std::getline(flux, string) pour "Tant qu'il y a une ligne a lire"
			iss.str(var.substr(0,var.find_first_of(";"))); //on transforme le premier char en int pour etre compare
			if(iss>>idActuel)
			{
			}
			else
			{
				Menu::error("Fichier corrompu1a.");
			}
			iss.clear();
		}
		if(idActuel==id)
		{
			int curseur;
			curseur=var.find_first_of(";");
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			std::string marque=var.substr(0,curseur);
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			std::string modele=var.substr(0,curseur);
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			std::string sIdEngine=var.substr(0,curseur);
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			std::string sIdSpoiler=var.substr(0,curseur);
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			std::string sIdAirIntake=var.substr(0,curseur);
			var.erase(0,curseur+1);

			curseur=var.find_first_of(";");
			std::string sNitroMax=var.substr(0,curseur);
			var.erase(0,curseur+1);

			std::string sAerodynamisme=var;

			int idEngine;
			int idSpoiler;
			int nitroMax;
			int idAirIntake;
			int aerodynamisme;

			iss.str(sIdEngine);
			if (iss>>idEngine)
			{
			}
			else
			{
				Menu::error("Fichier corrompu1b.");
			}
			iss.clear();
			iss.str(sIdSpoiler);
			if (iss>>idSpoiler)
			{
			}
			else
			{
				Menu::error("Fichier corrompu2.");
			}
			iss.clear();
			iss.str(sIdAirIntake);
			if (iss>>idAirIntake)
			{
			}
			else
			{
				Menu::error("Fichier corrompu3.");
			}
			iss.clear();
			iss.str(sNitroMax);
			if (iss>>nitroMax)
			{
			}
			else
			{
				Menu::error("Fichier corrompu4.");
			}
			iss.clear();
			iss.str(sAerodynamisme);
			if (iss>>aerodynamisme)
			{
			}
			else
			{
				Menu::error("Fichier corrompu4.");
			}
			iss.clear();
			CarCharge = new Car(marque, modele, idEngine, idSpoiler, idAirIntake, rangCharge, nitroMax, aerodynamisme, 1);
		}
		else
		{
			Menu::error("Fichier corrompu.");
		}
	}
	return CarCharge;
}

void Car::listerCars(const char& rang)
{
	std::string chemin ="Data/Cars/" + std::string(&rang) + ".cdx";
	std::string var;
	int prixEngine=0;

	std::ifstream flux(chemin.c_str());
	if(flux)
	{
		int curseur;
		Terminal::get() <<"   |Marque   |Modele     |Capacite nitro  |Aerodynamisme  |Prix  |\n\n";
		while(std::getline(flux, var))
		{
			curseur=var.find_first_of(";");
			std::string id=var.substr(0,curseur);
			var.erase(0,curseur+1);
			curseur=var.find_first_of(";");
			std::string marque=var.substr(0,curseur);
			var.erase(0,curseur+1);
			curseur=var.find_first_of(";");
			std::string modele=var.substr(0,curseur);
			var.erase(0,curseur+1);
			curseur=var.find_first_of(";");
			std::string sIdEngine=var.substr(0,curseur);
			var.erase(0,curseur+1);
			curseur=var.find_first_of(";");
			var.erase(0,curseur+1);
			curseur=var.find_first_of(";");
			var.erase(0,curseur+1);
			curseur=var.find_first_of(";");
			std::string sNitroMax=var.substr(0,curseur);
			std::string ssNitroMax= sNitroMax + "L";
			var.erase(0,curseur+1);
			std::string sAerodynamisme=var;
			std::string ssAerodynamisme = sAerodynamisme + "%";
			std::string espace1;
			std::string espace2;
			std::string espace3;
			std::string espace4;
			std::string espace5;
			if(marque.size()<10)
			{
				for (size_t i=0; i<10-marque.size(); i++)
				{
					espace1+=" ";
				}
			}
			if(modele.size()<12)
			{
				for (size_t i=0; i<12-modele.size(); i++)
				{
					espace2+=" ";
				}
			}
			if(ssNitroMax.size()<17)
			{
				for (size_t i = 0; i<17 - ssNitroMax.size(); i++)
				{
					espace3+=" ";
				}
			}
			if(ssAerodynamisme.size()<16)
			{
				for (size_t i=0; i<16-ssAerodynamisme.size(); i++)
				{
					espace4+=" ";
				}
			}
			if(id.size()<3)
			{
				for (size_t i=0; i<3-id.size(); i++)
				{
					espace5+=" ";
				}
			}
			int nitroMax;
			int aerodynamisme;
			int idEngine;
			std::istringstream iss(sNitroMax);
			if (iss>>nitroMax)
			{
			}
			else
			{
				Menu::error("Fichier corrompu9.");
			}
			iss.clear();
			iss.str(sAerodynamisme);
			if (iss>>aerodynamisme)
			{
			}
			else
			{
				Menu::error("Fichier corrompu10.");
			}
			iss.clear();
			iss.str(sIdEngine);
			if (iss>>idEngine)
			{
			}
			else
			{
				Menu::error("Fichier corrompu11.");
			}
			Engine::infoEngine(idEngine, marque, prixEngine);
			int prix = roundf( (prixEngine + 0 + 0 + 0 )  *0.85+ (( aerodynamisme + nitroMax ) * 100)+ (( vRang(rang) - 1 ) * 20000));
			Terminal::get() << id << "." << espace5 << marque << espace1 << modele << espace2 << ssNitroMax << espace3 << ssAerodynamisme << espace4 << prix << "c\n";
		}
	}
}

int Car::compterCars(const char& rang)
{
	std::string sRang;
	sRang=rang;
	std::string chemin ="Data/Cars/"+sRang+".cdx";
	std::ifstream engine(chemin.c_str());
	int id; //indique l'id actuellement lu dans le fichier
	int nbCar=0;
	std::string var;

	if(engine)
	{
		while(std::getline(engine, var))
		{
			 //on lit dans le fichier
			std::istringstream iss(var.substr(0,var.find_first_of(";"))); //on transforme le premier char en int pour etre compare
			if(iss>>id)
			{
				nbCar++;
			}
			else
			{
				Menu::error("Fichier corrompu6");
			}
			//on utilise while(std::getline(flux, string) pour "Tant qu'il y a une ligne a lire"
		}
	}
	else
	{
		Menu::error("Fichier corrompu7");
	}
	return nbCar;
}

void Car::infoCar(const int& id, const char& rang, std::string& marque, std::string& modele, int& idEngine, int& nitroMax, int& aerodynamisme, int& prix)
{
	std::string var; //contient les lignes du fichier
	std::string sRang;
	sRang=rang;
	std::string nomEngine;
	std::string chemin ="Data/Cars/"+sRang+".cdx";
	std::ifstream engine(chemin.c_str());

	if(!engine)
	{
		Menu::error("Echec de lecture du fichier "+sRang+".cdx");
	}
	else
	{
		int idActuel; //indique l'id actuellement lu dans le fichier
		while(idActuel!=id && std::getline(engine, var))
		{
			std::istringstream iss(var.substr(0,var.find_first_of(";"))); //on transforme le premier char en int pour etre compare
			if(iss>>idActuel)
			{
			}
			else
			{
				Menu::error("Fichier corrompu8");
			}
		}
		if(idActuel==id)
		{
			int curseur;
			var.erase(0,var.find_first_of(";")+1);
			curseur=var.find_first_of(";");
			marque=var.substr(0,curseur);
			var.erase(0,curseur+1);
			curseur=var.find_first_of(";");
			modele=var.substr(0,curseur);
			var.erase(0,curseur+1);
			curseur=var.find_first_of(";");
			std::string sIdEngine=var.substr(0,curseur);
			var.erase(0,curseur+1);
			curseur=var.find_first_of(";");
			std::string sIdSpoiler=var.substr(0,curseur);
			var.erase(0,curseur+1);
			curseur=var.find_first_of(";");
			std::string sIdAirIntake=var.substr(0,curseur);
			var.erase(0,curseur+1);
			curseur=var.find_first_of(";");
			std::string sNitro=var.substr(0,curseur);
			var.erase(0,curseur+1);
			std::string sAerodynamisme=var;
			std::istringstream iss(sNitro);
			if (iss>>nitroMax)
			{
			}
			else
			{
				Menu::error("Fichier corrompu9.");
			}
			iss.clear();
			iss.str(sAerodynamisme);
			if (iss>>aerodynamisme)
			{
			}
			else
			{
				Menu::error("Fichier corrompu10.");
			}
			iss.clear();
			iss.str(sIdEngine);
			if (iss>>idEngine)
			{
			}
			else
			{
				Menu::error("Fichier corrompu11.");
			}
			Engine::infoEngine(idEngine, marque, nomEngine);
			int prixEngine=0;
			Engine::infoEngine(idEngine, marque, prixEngine);
			prix=roundf( (prixEngine + 0 + 0 + 0 )  *0.85+ (( aerodynamisme + nitroMax ) * 100)+ (( vRang(rang) - 1 ) * 20000));
		}
		else
		{
			Menu::error("Fichier corrompu12.");
		}
	}
}

float Car::getVitesse() const
{
	return (_engine->getVitesse() + ( getAerodynamisme() / 3 ));
}

float Car::getAcceleration() const
{
	return (static_cast<float>((( _nitro + _engine->getAcceleration() ) + (getAerodynamisme())/10)));
}

int Car::getAerodynamisme() const
{
	return static_cast<float>((m_priseAir.getAerodynamic() / 3) + (m_spoiler.getAerodynamic() / 3) + (m_aerodynamismeCar / 3));;
}

int Car::getNitroMax() const
{
	return _nitroMax;
}

int Car::getNiveauNitro() const
{
	return _nitro;
}

int Car::getEtat() const
{
	return m_etat;
}

int Car::getPrix() const
{
	int prixEngine=0;
	int prixSpoiler=0;
	int prixAirIntake=0;
	Engine::infoEngine(m_idEngine, m_marque, prixEngine);
	prixSpoiler = Spoiler::collection[_spoiler].getPrice();
	prixAirIntake = AirIntake::collection[_airIntake].getPrice();

	return static_cast<int>(roundf( (prixEngine + prixSpoiler + prixAirIntake + 0 )  *0.9+ (( m_aerodynamismeCar + m_nitroMax ) * 100)+ (( vRang(m_rang) - 1 ) * 20000)));
}

Engine &Car::getEngine()
{
	return _engine;
}

Spoiler &Car::getSpoiler()
{
	return _spoiler;
}

AirIntake &Car::getAirIntake()
{
	return _airIntake;
}

Tires &Car::getTires()
{
	return _tires;
}

void Car::setEngine(Engine newEngine)
{
	_engine = newEngine;
	updateAttributs();
}

void Car::setSpoiler(Spoiler newSpoiler)
{
	_spoiler = newSpoiler;
	updateAttributs();
}

void Car::setAirIntake(AirIntake newAirIntake)
{
	_airIntake = newAirIntake;
	updateAttributs();
}

void Car::setTires(Tires tires)
{
	_tires = tires;
	updateAttributs();
}

void Car::setNitro(const int& ajouter)
{
	_nitro += ajouter;
	updateAttributs();
}

void Car::retirerEtat(const int& retirer)
{
	_durability -= retirer;
}

void Car::pleinNitro()
{
	_nitro = _nitroMax;
	updateAttributs();
}

void Car::pleinCarburant()
{
	updateAttributs();
}

void Car::reparer()
{
	_durability = 100;
}

void Car::updateAttributs()
{
	_nitro = _nitroMax;
}

void Car::changerTires()
{
	_tires.setDurability(100);
}