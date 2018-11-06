#include "Garage.hh"

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

Car &Garage::getBox(int index)
{
  return (*_boxs[index]);
}

size_t Garage::getBoxCount()
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