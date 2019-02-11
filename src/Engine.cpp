#include "Engine.hh"

Collection<Engine> Engine::collection = Collection<Engine>();

Engine::Engine(const json &data)
 : Part(data), mPower(data["power"].get<int>()),
 	mRevolutions(data["revolutions"].get<int>()), energy(Diesel),
  price((mPower.count()*25)+(vRang(rank)*500)), gear(0), power(0),
	revolutions(0), torque(0)
{

}

std::string Engine::info()
{
	return (Part::info() + " " + std::to_string(mPower.count()));
}

//Called every second
void Engine::update(omni::KilometerPerHour speed, omni::Inch diameter)
{
	revolutions = omni::revolutionPerMinute<int>((speed * omni::revolution<int>(1)) / (omni::pi::value * diameter) * (1/gearMultiplier[gear]));
	if (revolutions < omni::revolutionPerMinute<int>(800)) revolutions = 800;
	torque = (mPower / omni::pow<2>(mRevolutions)) * revolutions;
	power = torque * revolutions;
	if (revolutions > mRevolutions && gear < 5) gear++;
}