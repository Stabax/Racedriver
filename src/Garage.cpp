#include "Garage.hh"
#include "Profile.hh"

Garage::Garage()
{
}

Garage::Garage(const json &data)
{
  for (size_t i = 0; i < data.size(); i++)
  {
    _boxs.push_back(std::make_shared<Car>(data[i]));
  }
}

Car &Garage::selectCar() const
{
	int choice;

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

Car &Garage::getBox(int index) const
{
  return (*_boxs[index]);
}

size_t Garage::getBoxCount() const
{
  return (_boxs.size());
}


void Garage::displayBoxList()
{
  for (size_t i = 0; i < _boxs.size(); i++)
  {
    Terminal::get() << i << ". [" << _boxs[i]->manufacturer << " " << _boxs[i]->name << "]\n";
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
									<< " |Capacite Nitro: " << car->getNitroMax() << " L\n"
									<< " |Aerodynamisme: " << car->getAerodynamisme() << " %\n"
									<< " |Nitro Actuelle: " << car->getNiveauNitro() << " L\n"
									<< " |Durabilite Tires: "<< car->getTires()->getDurability() << "%\n"
									<< " |Etat: " << car->getEtat() << "%\n\n"
									<< "#Engine\n"
									<< " |Modele: " << car->getEngine()->name << "\n"
									<< " |Vitesse: "<< car->getEngine()->getVitesse() << " Km/h\n"
									<< " |Acceleration: " << car->getEngine()->getAcceleration() << " m/s²\n\n"
									<< "#Spoiler\n"
									<< " |Modele: " << car->getSpoiler()->name << "\n"
									<< " |Rang: "<<  car->getSpoiler()->rank << "\n"
									<< " |Aerodynamisme: " <<  car->getSpoiler()->getAerodynamic() << " %\n\n"
									<< "#Prises d'air\n"
									<< " |Modele: " << car->getAirIntake()->name << "\n"
									<< " |Rang: "<<  car->getAirIntake()->rank << "\n"
									<< " |Aerodynamisme: " <<  car->getAirIntake()->getAerodynamic() << " %\n\n"
									<< "#Tires\n"
									<< " |Modele: " << car->getTires()->name << "\n"
									<< " |Rang: "<<  car->getTires()->rank << "\n"
									<< "===============\n"
									<< "Appuyez sur Entree pour revenir au menu precedent";
	getch();
}

void to_json(json& j, const Garage& garage)
{
	j = json::array();
	for (size_t i = 0; i < garage.getBoxCount(); i++)
	{
		j.push_back(garage.getBox(i));
	}
}