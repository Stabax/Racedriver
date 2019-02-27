//Car.cpp
#include "Car.hh"
#include "Menu.hh"
#include "Profile.hh"

Collection<Car> Car::collection = Collection<Car>();

Car::Car(const json &data)
 : Part(data, TCar),
 	integrity(data.find("integrity") != data.end() ? data["integrity"].get<int>() : 100), nitro(100),
	fuel(data.find("fuel") != data.end() ? data["fuel"].get<float>() : 0), speed(0), acceleration(0), fc(0)
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
	socket = toCopy.socket;
	mass = toCopy.mass;
	price = toCopy.price;
}

void Car::expose(sol::environment &lua)
{
	lua.new_usertype<Car>("Car",
		// constructor
		sol::constructors<Car(const json &)>(),

		"getId", &Car::getId,
		"getTotalPrice", &Car::getTotalPrice,
		"buyEngine", &Car::buyEngine,
		"buySpoiler", &Car::buySpoiler,
		"buyTires", &Car::buyTires,

		"name", &Car::name,
		"manufacturer", &Car::manufacturer,
		"mass", &Car::mass,
		"price", &Car::price,

		"getEngine", &Car::getEngine,
		"getSpoiler", &Car::getSpoiler,
		"getTires", &Car::getTires
	);
}

bool Car::update(const omni::Minute &tickDuration, const Segment &segment)
{
	_engine->update(speed, _tires->diameter);
	omni::Horsepower power = _engine->power;
  omni::Watt cineticDiff = power - (mass * omni::MeterPerSecond2(9.81) * (speed > omni::KilometerPerHour(0) ? (segment.gradient / (speed * tickDuration)) : 0) * speed);
	omni::NewtonMeter cinetic;
	if (speed > omni::KilometerPerHour(0)) cinetic = 0.5 * mass * omni::pow<2>(speed);
	else cinetic = cineticDiff * tickDuration;

	acceleration = omni::nroot<2>(2 / (mass * cinetic)) * (cineticDiff / 2);
	omni::Newton rWind = MillinewtonHour2PerKilometer2(350) * omni::pow<2>(speed) * (omni::Value(1.5) - omni::Percent(getAerodynamic()));
	omni::Newton rGround = MillinewtonHourPerKilometer(500) * speed * (_tires->mPressure /_tires->pressure) * omni::exp(_tires->integrity * 3);
	acceleration -= (rWind / mass) - (rGround / mass);
	speed += acceleration * tickDuration;
	if (segment.getRadius() != omni::Meter(0)) fc = mass * omni::pow<2>(speed) / segment.getRadius();
	else fc = omni::Newton(0);
	if (fc > omni::Newton(1)) return (false);
	return (true);
}

omni::Percent Car::getAerodynamic() const
{
	return (_spoiler != nullptr ? _spoiler->aerodynamic : omni::Percent(0));
}

int Car::getTotalPrice() const
{
	return (price + _engine->price + _spoiler->price + _tires->price);
}

Engine &Car::getEngine() const
{
	return (*_engine);
}

Spoiler &Car::getSpoiler() const
{
	return (*_spoiler);
}

Tires &Car::getTires() const
{
	return (*_tires);
}

void Car::buyEngine(const Engine &newEngine)
{
	if (!Profile::active->pay(newEngine.price)) return;
	_engine = std::make_shared<Engine>(newEngine);
	updateAttributs();
}

void Car::buySpoiler(const Spoiler &newSpoiler)
{
	if (!Profile::active->pay(newSpoiler.price)) return;
	_spoiler = std::make_shared<Spoiler>(newSpoiler);
	updateAttributs();
}

void Car::buyTires(const Tires &newTires)
{
	if (!Profile::active->pay(newTires.price)) return;
	_tires = std::make_shared<Tires>(newTires);
	updateAttributs();
}

void Car::setNitro(omni::Liter ajouter)
{
	nitro += ajouter;
	updateAttributs();
}

void Car::pleinNitro()
{
	nitro = omni::Liter(100);
	updateAttributs();
}

void Car::pleinCarburant()
{
	updateAttributs();
}

void Car::reparer()
{
	integrity = 100;
}

void Car::updateAttributs()
{
	nitro = omni::Liter(100);
}

void Car::replaceTires()
{
	_tires->integrity = 100;
}

void to_json(json& j, const Car& car) {
	j = {
		{"name", car.getId()},
		{"engine", car.getEngine().getId()},
    {"spoiler", car.getSpoiler().getId()},
    {"tires", {
			{"id", car.getTires().getId()},
			{"integrity", car.getTires().integrity.count()}
		}},
		{"fuel", car.fuel.count()},
		{"integrity", car.integrity.count()}
	};
}
