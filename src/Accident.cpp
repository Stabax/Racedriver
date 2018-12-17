#include "Accident.hh"

std::vector<Accident> Accident::collection = std::vector<Accident>();

Accident::Accident(const json &data)
: damage(data["damage"].get<int>()), message(data["message"].get<std::string>())
{

}

void Accident::loadCollection()
{
	DataFile file("./Data/Events/Crash.json");

	if (!file.load())
	{
		throw (std::runtime_error("Error loading Crash"));
	}
	const json &data = file.getData();
	for (size_t i = 0; i < data["collection"].size(); i++)
	{
		collection.push_back(Accident(data["collection"][i]));
	}
}