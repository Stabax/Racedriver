#include "Engine.hh"

Collection<Engine> Engine::collection = Collection<Engine>();

Engine::Engine(const json &data)
 : Part(data, TEngine), mPower(data["power"].get<int>()),
 	mRevolutions(data["revolutions"].get<int>()), mTorque(mPower / mRevolutions),
	mGears(data["gears"].get<int>()), energy(Diesel), gear(0), power(0),
	revolutions(0), torque(0)
{
}

void Engine::expose(sol::environment &lua)
{
	lua.new_usertype<Engine>("Engine",
		// constructor
		sol::constructors<Engine(const json &data)>(),

		"getId", &Engine::getId,
		"name", &Engine::name,
		"manufacturer", &Engine::manufacturer,
		"price", &Engine::price,

		"getPower", &Engine::getPower,
		"getRevolutions", &Engine::getRevolutions,
		"gears", &Engine::mGears
	);
}

std::string Engine::getPower()
{
	return (std::to_string(mPower.count()));
}

std::string Engine::getRevolutions()
{
	return (std::to_string(mRevolutions.count()));
}

std::string Engine::info()
{
	return (Part::info() + " " + std::to_string(mPower.count()));
}

//Called every second
void Engine::update(omni::KilometerPerHour speed, omni::Inch diameter)
{
	revolutions = omni::revolutionPerMinute<int>((speed * omni::revolution<int>(1)) / (omni::pi::value * diameter) * gearMultiplier[gear] * 3.5);
	if (revolutions < omni::revolutionPerMinute<int>(800)) revolutions = 800;
	torque = (mPower / omni::pow<2>(mRevolutions)) * revolutions;
	if (revolutions > mRevolutions) torque = -torque + (2 * mTorque);
	if (torque < omni::NewtonMeter(0)) torque = 0;
	power = torque * revolutions;
	if (gear < mGears - 1)
	{
		if (revolutions < (mRevolutions + omni::revolutionPerMinute<int>(1000)) && (revolutions > mRevolutions + omni::revolutionPerMinute<int>(500)) && (rand() % 10 == 0)) gear++;
	 	else if (revolutions > (mRevolutions + omni::revolutionPerMinute<int>(1000))) gear++; //shift anyway
	}
}