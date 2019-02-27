#include "Garage.hh"
#include "Profile.hh"

Garage::Garage()
 : _boxCount(1)
{
}

Garage::Garage(const json &data)
{
	_boxCount = data["boxcount"];
	if (data.find("cars") == data.end()) throw (std::runtime_error("Corrupted garage data"));
  for (size_t i = 0; i < data["cars"].size(); i++)
  {
		try {
    	_boxs.push_back(std::make_shared<Car>(data["cars"][i]));
		} catch (std::exception &e) {
			throw (std::runtime_error("Corrupted car data"));
		}
  }
}


void Garage::expose(sol::environment &lua)
{
	lua.new_usertype<Garage>("Garage",
		// constructor
		sol::constructors<Garage(const json &data)>(),

		"boxCount", &Garage::_boxCount,

		"get", &Garage::get,
		"sellCar", &Garage::sellCar,
		"size", &Garage::getSize
	);
}


Car &Garage::get(size_t index) const
{
	if (_boxs.size() > 0 && index >= _boxs.size()) throw (std::runtime_error("Out of bounds"));
	if (_boxs[index] == nullptr) throw (std::runtime_error("Corrupted garage data"));
  return (*_boxs[index]);
}

size_t Garage::getSize() const
{
  return (_boxs.size());
}

size_t Garage::getBoxCount() const
{
  return (_boxCount);
}

bool Garage::addBox()
{
	if (!Profile::active->pay(_boxCount * 1000)) return (false);
	_boxCount++;
	Menu::alert("Garage agrandi avec succes!");
	return (true);
}

bool Garage::addCar(Car &car)
{
	if (_boxs.size() >= _boxCount)
	{
		Menu::alert("Plus de place disponible dans le garage");
		return (false);
	}
	_boxs.push_back(std::make_shared<Car>(car));
	return (true);
}

bool Garage::buyCar(Car &car)
{
	if (!Profile::active->pay(car.price)) return (false);
	if (addCar(car))
	{
		Menu::alert(car.name+" achetee avec succes !");
		return (true);
	}
	return (false);
}

void Garage::sellCar(size_t index)
{
	if (index >= _boxs.size())
	{
		throw (std::runtime_error("Le box est vide"));
	}
	Car &car = get(index);
	int sellPrice = car.getTotalPrice() * 0.70f;
	Profile::active->credits += sellPrice;
	Menu::alert(car.name+" vendue avec succes pour "+std::to_string(sellPrice)+"c");
	_boxs.erase(_boxs.begin() + index);
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
			Car &car = garage.get(i);
			j["cars"].push_back(car);
		} catch (...) {
			//Nothing to do
		}
	}
}