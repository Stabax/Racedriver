#include "Engine.hh"

Collection<Engine> Engine::collection = Collection<Engine>();

Engine::Engine(const json &data)
 : Part(data), mPower(data["power"].get<int>()),
 	mRevolutions(data["revolutions"].get<int>()), energy(Diesel),
  price((mPower.count()*25)+(vRang(rank)*500)), _power(0),
	_revolutions(0), _torque(0)
{

}

std::string Engine::info()
{
	return (Part::info() + " " + std::to_string(mPower.count()));
}

omni::Horsepower Engine::getPower()
{
	return (_power);
}

//Called every second
void Engine::update(omni::KilometerPerHour speed, omni::Inch radius)
{
	_revolutions = omni::turnPerMinute<int>(speed / (2 * omni::pi::value * radius)) * 1;
	if (_revolutions < omni::turnPerMinute<int>(800)) _revolutions = 800;
	_torque = ((_revolutions > mRevolutions ? -1  : 1) * mPower / omni::pow<2>(mRevolutions)) * _revolutions;
	_power = _torque * _revolutions;
}