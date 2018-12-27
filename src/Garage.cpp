#include "Garage.hh"
#include "Profile.hh"
#include "sousMenus.hh"

Garage::Garage()
 : _boxCount(1)
{
}

Garage::Garage(const json &data)
{
	_boxCount = data["boxcount"];
  for (size_t i = 0; i < data["cars"].size(); i++)
  {
    _boxs.push_back(std::make_shared<Car>(data["cars"][i]));
  }
}

Car &Garage::selectCar() const
{
	int choice;

	Terminal::get().clearScreen();
	Terminal::get() << "Liste des Boxs\n"
									<< "===============\n"
									<< "Selectionnez le vehicule qui va faire la course.\n"
									<< "===============\n\n";
	Profile::active->garage.displayBoxList();
	Terminal::get() << "\n" //On separe le bloc
									<< "0. Retour\n";
	if ((choice = Menu::askChoice()) > 0)
	{
		return (Profile::active->garage.getBox(choice - 1));
	}
	else
	{
		Menu::error("Saisie invalide");
		throw std::runtime_error("Bad index");
	}
}

Car &Garage::getBox(size_t index) const
{
	if (index >= _boxs.size()) throw (std::runtime_error("Out of bounds"));
  return (*_boxs[index]);
}

size_t Garage::getBoxCount() const
{
  return (_boxCount);
}

bool Garage::addCar(Car &car)
{
	if (_boxs.size() >= _boxCount)
	{
		Menu::error("Plus de place disponible dans le garage");
		return (false);
	}
	_boxs.push_back(std::make_shared<Car>(car));
	return (true);
}

void Garage::sellCar(size_t index)
{
	if (index >= _boxs.size())
	{
		throw (std::runtime_error("Le box est vide"));
	}
	Car &car = getBox(index);
	int sellPrice = car.getPrix() * 0.70f;
	Profile::active->credits += sellPrice;
	Menu::msg(car.name+" vendue avec succes pour "+std::to_string(sellPrice)+"c");
	_boxs.erase(_boxs.begin() + index);
}

void Garage::displayBoxList()
{
  for (size_t i = 0; i < _boxs.size(); i++)
  {
    Terminal::get() << i+1 << ". [" << _boxs[i]->manufacturer << " " << _boxs[i]->name << "]\n";
  }
}

void Garage::displayBoxDetail(int index)
{
  auto car = _boxs[index];
	Terminal::get() << "Vehicule gare dans le Box " << index << "\n"
									<< "===============\n\n"
									<< "#Vehicule\n"
									<< " |Modele: " << car->name << "\n"
									<< " |Marque: " << car->manufacturer << "\n"
									<< " |Rang: " << car->rank << "\n"
									<< " |\n"
									<< " |Vitesse Totale: "<< car->getVitesse() << " Km/h\n"
									<< " |Acceleration Totale: " << car->getAcceleration() << " m/s²\n"
									<< " |Capacite Nitro: " << 100 << " L\n"
									<< " |Aerodynamisme: " << car->getAerodynamisme() << " %\n"
									<< " |Nitro Actuelle: " << car->getNiveauNitro() << " L\n"
									<< " |Durabilite Tires: "<< car->getTires()->getDurability() << "%\n"
									<< " |Etat: " << car->getDurability() << "%\n\n"
									<< "#Engine\n"
									<< " |Modele: " << car->getEngine()->name << "\n"
									<< " |Puissance: "<< car->getEngine()->getPower() << " ch\n"
									<< " |Couple: " << car->getEngine()->getTorque() << " nm\n\n"
									<< "#Spoiler\n";
	if (car->getSpoiler() != nullptr)
	{
		Terminal::get() << " |Modele: " << car->getSpoiler()->name << "\n"
										<< " |Marque: " << car->getSpoiler()->manufacturer  << "\n"
										<< " |Rang: "<<  car->getSpoiler()->rank << "\n"
										<< " |Aerodynamisme: " <<  car->getSpoiler()->getAerodynamic() << " %\n\n";
	}
	else
	{
		Terminal::get() << " |Aucun\n";
	}
	Terminal::get() << "#Pneus\n"
									<< " |Modele: " << car->getTires()->name << "\n"
									<< " |Marque: " << car->getTires()->manufacturer << "\n"
									<< " |Rang: "<<  car->getTires()->rank << "\n"
									<< "===============\n"
									<< "1. Atelier\n"
									<< "2. Vendre\n"
									<< "0. Retour\n";
	switch(Menu::askChoice())
	{
		case 0:
			break;
		case 1:
			menuAtelier(index);
			break;
		case 2:
			Profile::active->garage.sellCar(index);
			break;
	}
}

void to_json(json& j, const Garage& garage)
{
	j = {
		{"boxcount", garage.getBoxCount()},
		{"cars", json::array()}
	};
	for (size_t i = 0; i < garage.getBoxCount(); i++)
	{
		try {
			Car &car = garage.getBox(i);
			j["cars"].push_back(car);
		} catch (...) {
			//Nothing to do
		}
	}
}