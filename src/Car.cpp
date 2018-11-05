//Car.cpp
#include "Car.hh"
#include "Menu.hh"

std::map<std::string, Car> Car::collection = std::map<std::string, Car>();

Car::Car(const json &data)
 : Part(data), _engine(std::make_shared<Engine>(Engine::collection.at(data["engine"]))), _spoiler(std::make_shared<Spoiler>(Spoiler::collection.at(data["spoiler"]))),
  _airIntake(std::make_shared<AirIntake>(AirIntake::collection.at(data["airIntake"]))), _tires(std::make_shared<Tires>(Tires::collection.at(data["tires"]))), _nitroMax(100),
  _nitro(_nitroMax), _durability(100)
{

}

Car::~Car()
{
}

void Car::listerCars()
{
	int i = 0;

	Terminal::get() <<"   |Marque   |Modele     |Capacite nitro  |Aerodynamisme  |Prix  |\n\n";
  for (auto it = Car::collection.begin(); it != Car::collection.end(); ++it)
	{
		Terminal::get() << i << "." << it->second.manufacturer << " " << it->second.name << " " << it->second.getNitroMax()
										<< " " << it->second.getAerodynamisme() << " " << it->second.getPrix() << "c\n";
		++i;
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
	return static_cast<float>((_airIntake->getAerodynamic() / 3) + (_spoiler->getAerodynamic() / 3) );
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
	return _durability;
}

int Car::getPrix() const
{
	int prixEngine=0;
	int prixSpoiler=0;
	int prixAirIntake=0;
	prixSpoiler = _spoiler->getPrice();
	prixAirIntake = _airIntake->getPrice();

	return static_cast<int>(roundf( (prixEngine + prixSpoiler + prixAirIntake + 0 )  *0.9+ (( _nitroMax ) * 100)+ (( vRang(rank) - 1 ) * 20000)));
}

std::shared_ptr<Engine> Car::getEngine()
{
	return _engine;
}

std::shared_ptr<Spoiler> Car::getSpoiler()
{
	return _spoiler;
}

std::shared_ptr<AirIntake> Car::getAirIntake()
{
	return _airIntake;
}

std::shared_ptr<Tires> Car::getTires()
{
	return _tires;
}

void Car::setEngine(const Engine &newEngine)
{
	_engine = std::make_shared<Engine>(newEngine);
	updateAttributs();
}

void Car::setSpoiler(const Spoiler &newSpoiler)
{
	_spoiler = std::make_shared<Spoiler>(newSpoiler);
	updateAttributs();
}

void Car::setAirIntake(const AirIntake &newAirIntake)
{
	_airIntake = std::make_shared<AirIntake>(newAirIntake);
	updateAttributs();
}

void Car::setTires(const Tires &tires)
{
	_tires = std::make_shared<Tires>(tires);
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
	_tires->setDurability(100);
}