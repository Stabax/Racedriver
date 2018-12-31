#include "Engine.hh"

Collection<Engine> Engine::collection = Collection<Engine>();

Engine::Engine(const json &data)
 : Part(data), mPower(data["power"].get<int>()), energy(Diesel), price((mPower*25)+(vRang(rank)*500)), _mRevolutions(data["revolutions"].get<int>()),
  _torque(0)
{

}

std::string Engine::info()
{
	return (Part::info() + " " + std::to_string(mPower));
}

int Engine::getPower()
{
	return (_power);
}

//Called every second
void Engine::update(int speed, int radius)
{
	_revolutions = (speed < 5 ? 800 : (speed / 2 * 3.14 * radius) * 1);
	_torque = (_revolutions > _mRevolutions ? -(mPower / (mPower * _mRevolutions))  : mPower / (mPower * _mRevolutions)) * _revolutions;
	_power = _torque * _revolutions;
}