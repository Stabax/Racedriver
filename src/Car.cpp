//Car.cpp
#include "Car.hh"
#include "Menu.hh"

Collection<Car> Car::collection = Collection<Car>();

Car::Car(const json &data)
 : Part(data), _engine(std::make_shared<Engine>(Engine::collection[data["engine"].get<std::string>()])), _spoiler(std::make_shared<Spoiler>(Spoiler::collection[data["spoiler"].get<std::string>()])),
  _airIntake(std::make_shared<AirIntake>(AirIntake::collection[data["airIntake"].get<std::string>()])), _tires(std::make_shared<Tires>(Tires::collection[data["tires"].get<std::string>()])), _nitroMax(100),
  _nitro(_nitroMax), _durability(100)
{

}

Car::~Car()
{
}

void Car::displayInfo() const
{
	Terminal::get() << " |Marque: " << manufacturer << "\n"
									<< " |Modele: " << name << "\n"
									<< " #Engine" << "\n"
									<< "  |Marque: " << manufacturer << "\n"
									<< "  |Modele: " << name << "\n"
									<< "  |Vitese: " << "Km/h\n"
									<< "  |Acceleration: " << "m/s²\n"
									<< " |Capa. Nitro: " << "L\n"
									<< " |Aerodynamisme: " << "%\n"
									<< " |Prix: " << "c\n\n";
}

void Car::listerCars()
{
	int i = 0;

	Terminal::get() << "   |Marque   |Modele     |Capacite nitro  |Aerodynamisme  |Prix  |\n\n";
  /*for (auto it = Car::collection.begin(); it != Car::collection.end(); ++it)
	{
		Terminal::get() << i << "." << it->second.manufacturer << " " << it->second.name << " " << it->second.getNitroMax()
										<< " " << it->second.getAerodynamisme() << " " << it->second.getPrix() << "c\n";
		++i;
	}*/
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

std::shared_ptr<Engine> Car::getEngine() const
{
	return (_engine);
}

std::shared_ptr<Spoiler> Car::getSpoiler() const
{
	return (_spoiler);
}

std::shared_ptr<AirIntake> Car::getAirIntake() const
{
	return (_airIntake);
}

std::shared_ptr<Tires> Car::getTires() const
{
	return (_tires);
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

void to_json(json& j, const Car& car) {
	j = {
		{"name", car.getId()},
		{"engine", car.getEngine()->getId()},
    {"airIntake", car.getAirIntake()->getId()},
    {"spoiler", car.getSpoiler()->getId()},
    {"tires", car.getTires()->getId()}
	};
}
