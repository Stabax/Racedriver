//Car.cpp
#include "Car.hh"
#include "Menu.hh"
#include <cmath>

Collection<Car> Car::collection = Collection<Car>();

Car::Car() : Part() {} //Dummy for lua

Car::Car(const json &data)
 : Part(data),
	_mass(data.find("mass") != data.end() ? data["mass"].get<int>() : -1),
 	_integrity(data.find("integrity") != data.end() ? data["integrity"].get<int>() : 100), _nitro(100),
	_fuel(data.find("fuel") != data.end() ? data["fuel"].get<float>() : 0), _speed(0), _acceleration(0)
{
  copy(data["name"].get<std::string>()); //Copy if needed
 	_engine = std::make_shared<Engine>(Engine::collection[data["engine"].get<std::string>()]);
  if (data["spoiler"].get<std::string>() != "") _spoiler = std::make_shared<Spoiler>(Spoiler::collection[data["spoiler"].get<std::string>()]);
	if (data["tires"].find("id") != data["tires"].end()) //rebuild from save
	{
		_tires = std::make_shared<Tires>(Tires::collection[data["tires"]["id"].get<std::string>()]);
		if (data["tires"].find("integrity") != data["tires"].end()) _tires->integrity = data["tires"]["integrity"].get<int>();
	}
	else //build from factory
	{
		_tires = std::make_shared<Tires>(Tires::collection[data["tires"].get<std::string>()]);
	}
}

Car::~Car()
{
}

void Car::copy(const std::string &id)
{
	if (id.find(ID_SEPARATOR) == std::string::npos) return;
	Car &toCopy = collection[id];
	name = toCopy.name;
	manufacturer = toCopy.manufacturer;
	_mass = toCopy._mass;
	rank = toCopy.rank;
}

void Car::expose(sol::state &lua)
{
	lua.new_usertype<Car>("Car",
		// constructor
		sol::constructors<Car()>(),

		"name", &Car::name,
		"manufacturer", &Car::manufacturer
	);
}


void Car::displayInfo() const
{
	/*
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
									*/
}

void Car::listerCars()
{
	/*
	Terminal::get() << "   |Marque   |Modele     |Aerodynamisme  |Prix  |\n\n";
  for (size_t i = 0; i < Car::collection.size(); i++)
	{
		Terminal::get() << i+1 << "." << Car::collection[i].manufacturer << " " << Car::collection[i].name
												 << " " << Car::collection[i].getAerodynamisme() << " " << Car::collection[i].getPrix() << "c\n";
	}*/
}

void Car::update(omni::Minute tickDuration, omni::Meter gradient)
{
	_engine->update(_speed, _tires->radius);
	omni::Horsepower power = _engine->getPower();
  omni::Watt cineticDiff = power - (_mass * omni::MeterPerSecond2(9.81) * (_speed > omni::KilometerPerHour(0) ? (gradient / (_speed * tickDuration)) : 0) * _speed);
	omni::NewtonMeter cinetic;
	if (_speed > omni::KilometerPerHour(0)) cinetic = 0.5 * _mass * omni::pow<2>(_speed);
	else cinetic = cineticDiff * tickDuration;

	_acceleration = omni::nroot<2>(2 / (_mass * cinetic)) * (cineticDiff / 2);
	_speed = _acceleration * tickDuration;
	omni::Newton rWind = NewtonHour2PerKilometer2(1) * omni::pow<2>(_speed) * (omni::Value(1.5) - omni::Percent(getAerodynamic()));
	omni::Newton rSol = NewtonHourPerKilometer(1) * _speed * (_tires->mPressure /_tires->pressure) * omni::exp(omni::Percent(_tires->integrity) * 3);
}

omni::KilometerPerHour Car::getSpeed() const
{
	return (_speed);
}

omni::MeterPerSecond2 Car::getAcceleration() const
{
	return (static_cast<float>(((_nitro.count()) + (getAerodynamic())/10)));
}

int Car::getAerodynamic() const
{
	float spoilerValue = (_spoiler != nullptr ? _spoiler->getAerodynamic() : 0);
	return (spoilerValue);
}

omni::Liter Car::getNiveauNitro() const
{
	return _nitro;
}

int Car::getDurability() const
{
	return _integrity;
}

omni::Liter Car::getFuel() const
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

void Car::setNitro(omni::Liter ajouter)
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
	_nitro = omni::Liter(100);
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
	_nitro = omni::Liter(100);
}

void Car::replaceTires()
{
	_tires->integrity = 100;
}

void to_json(json& j, const Car& car) {
	j = {
		{"name", car.getId()},
		{"engine", car.getEngine()->getId()},
    {"spoiler", (car.getSpoiler() != nullptr ? car.getSpoiler()->getId() : "")},
    {"tires", {
			{"id", car.getTires()->getId()},
			{"integrity", car.getTires()->integrity}
		}},
		{"fuel", car.getFuel().count()},
		{"integrity", car.getDurability()}
	};
}
