//Car.cpp
#include "Car.hh"
#include "Menu.hh"

Collection<Car> Car::collection = Collection<Car>();

Car::Car(const json &data)
 : Part(data), _nitro(100),
 	_fuel(data.find("fuel") != data.end() ? data["fuel"].get<float>() : 0),
 	_integrity(data.find("integrity") != data.end() ? data["integrity"].get<int>() : 100)
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
	if (data["tires"].find("id") != data["tires"].end()) //rebuild from save
	{
		_tires = std::make_shared<Tires>(Tires::collection[data["tires"]["id"].get<std::string>()]);
		if (data["tires"].find("integrity") != data["tires"].end()) _tires->setIntegrity(data["tires"]["integrity"].get<int>());
	}
	else //build from factory
	{
		_tires = std::make_shared<Tires>(Tires::collection[data["tires"].get<std::string>()]);
	}
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
	Terminal::get() << "   |Marque   |Modele     |Aerodynamisme  |Prix  |\n\n";
  for (size_t i = 0; i < Car::collection.size(); i++)
	{
		Terminal::get() << i+1 << "." << Car::collection[i].manufacturer << " " << Car::collection[i].name
												 << " " << Car::collection[i].getAerodynamisme() << " " << Car::collection[i].getPrix() << "c\n";
	}
}

float Car::getVitesse() const
{
	return (_engine->getPower() + ( getAerodynamisme() / 3 ));
}

float Car::getAcceleration() const
{
	return (static_cast<float>((( _nitro + _engine->getTorque() ) + (getAerodynamisme())/10)));
}

int Car::getAerodynamisme() const
{
	float spoilerValue = (_spoiler != nullptr ? _spoiler->getAerodynamic() : 0);
	return (spoilerValue);
}

int Car::getNiveauNitro() const
{
	return _nitro;
}

int Car::getDurability() const
{
	return _integrity;
}

int Car::getFuel() const
{
	return _fuel;
}

int Car::getPrix() const
{
	int prixEngine = 0;
	int prixSpoiler = 0;
	prixSpoiler = (_spoiler != nullptr ? _spoiler->getPrice() : 0);
	return static_cast<int>(roundf( (prixEngine + prixSpoiler + 0 )  *0.9+ (( 100 ) * 100)+ (( vRang(rank) - 1 ) * 20000)));
}

std::shared_ptr<Engine> Car::getEngine() const
{
	return (_engine);
}

std::shared_ptr<Spoiler> Car::getSpoiler() const
{
	return (_spoiler);
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

void Car::damage(int value)
{
	_integrity -= value;
}

void Car::pleinNitro()
{
	_nitro = 100;
	updateAttributs();
}

void Car::pleinCarburant()
{
	updateAttributs();
}

void Car::reparer()
{
	_integrity = 100;
}

void Car::updateAttributs()
{
	_nitro = 100;
}

void Car::replaceTires()
{
	_tires->setIntegrity(100);
}

void to_json(json& j, const Car& car) {
	j = {
		{"name", car.getId()},
		{"engine", car.getEngine()->getId()},
    {"spoiler", (car.getSpoiler() != nullptr ? car.getSpoiler()->getId() : "")},
    {"tires", {
			{"id", car.getTires()->getId()},
			{"integrity", car.getTires()->getDurability()}
		}},
		{"fuel", car.getFuel()},
		{"integrity", car.getDurability()}
	};
}
