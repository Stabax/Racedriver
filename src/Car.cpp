//Car.cpp
#include "Car.hh"
#include "Menu.hh"

Collection<Car> Car::collection = Collection<Car>();

Car::Car(const json &data)
 : Part(data), _nitroMax(100), _nitro(_nitroMax), _durability(100)
{
	std::string id = data["name"].get<std::string>();
  if (id.find(ID_SEPARATOR) != std::string::npos)
	{
		Car &toCopy = collection[id];
		name = toCopy.name;
		manufacturer = toCopy.manufacturer;
		rank = toCopy.rank;
	}
 	_engine = std::make_shared<Engine>(Engine::collection[data["engine"].get<std::string>()]);
  if (data["spoiler"].get<std::string>() != "") _spoiler = std::make_shared<Spoiler>(Spoiler::collection[data["spoiler"].get<std::string>()]);
  if (data["airIntake"].get<std::string>() != "") _airIntake = std::make_shared<AirIntake>(AirIntake::collection[data["airIntake"].get<std::string>()]);
	_tires = std::make_shared<Tires>(Tires::collection[data["tires"].get<std::string>()]);
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
	Terminal::get() << "   |Marque   |Modele     |Capacite nitro  |Aerodynamisme  |Prix  |\n\n";
  for (size_t i = 0; i < Car::collection.size(); i++)
	{
		Terminal::get() << i << "." << Car::collection[i].manufacturer << " " << Car::collection[i].name << " " << Car::collection[i].getNitroMax()
										<< " " << Car::collection[i].getAerodynamisme() << " " << Car::collection[i].getPrix() << "c\n";
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
	float airIntakeValue = (_airIntake != nullptr ? _airIntake->getAerodynamic() : 0);
	float spoilerValue = (_spoiler != nullptr ? _spoiler->getAerodynamic() : 0);
	return (airIntakeValue + spoilerValue);
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
	prixSpoiler = (_spoiler != nullptr ? _spoiler->getPrice() : 0);
	prixAirIntake = (_airIntake != nullptr ? _airIntake->getPrice() : 0);

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
    {"airIntake", (car.getAirIntake() != nullptr ? car.getAirIntake()->getId() : "")},
    {"spoiler", (car.getSpoiler() != nullptr ? car.getSpoiler()->getId() : "")},
    {"tires", car.getTires()->getId()}
	};
}
