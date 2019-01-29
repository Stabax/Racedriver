//Profiles.cpp
#include "Profile.hh"
#include "Menu.hh"

std::shared_ptr<Profile> Profile::active = nullptr;

Profile::Profile(const std::string &name)
 : name(name), difficulty(Difficulty::Easy), credits(10000), garage()
{
	garage.addCar(Car::collection[0]);
}


Profile::Profile(const json &data)
 : name(data["name"].get<std::string>()), difficulty(data["difficulty"].get<Difficulty>()), credits(data["credits"].get<int>()), garage(data["garage"])
{

}

Profile::~Profile()
{
}

void Profile::create(const std::string &name)
{
	Profile::active = std::make_shared<Profile>(name);
}

void Profile::load(const std::string &save)
{
	DataFile file("./Data/Saves/"+save);

	if (!file.load())
	{
		throw std::runtime_error("Cannot load profile:"+save);
	}
	try {
		Profile::active = std::make_shared<Profile>(file.getData());
	} catch (std::exception &e) {
		throw std::runtime_error("Corrupted profile data");
	}
}

void Profile::save()
{
	DataFile save("./Data/Saves/"+name+".json");
	json data = *this;

	if (!save.save(data))
	{
		Menu::alert("Cannot save Profile: "+name);
	}
}

void Profile::displaySavesList()
{
	std::vector<std::string> saves = DataFile::getFolderContents("./Data/Saves/", ".json");
	saves.insert(saves.begin(), ""); //Dummy to keep index true

	for (size_t i = 1; i < saves.size(); i++)
	{
		Terminal::get() << i << ". " << saves[i] << "\n";
	}
}

void Profile::supprimerProfile([[maybe_unused]]const int& numeroSave)
{
	//Not implemented
}

bool Profile::rename(const std::string &n)
{
	if (!DataFile::rename(name, n))
	{
		throw (std::runtime_error("Could not rename profile"));
	}
	name = n;
	return (true);
}

bool Profile::payer(const int& prix)
{
	bool paye;
	if(prix > credits)
	{
		Menu::alert("Vous ne disposez pas d'assez de Credits !");
		paye = false;
	}
	else
	{
		credits -= prix;
		paye = true;
	}
	return paye;
}

void to_json(json& j, const Profile& profile) {
	json garage = profile.garage;
	j = {
		{"name", profile.name},
		{"difficulty", profile.difficulty},
		{"credits", profile.credits},
		{"careerStats", {
			{"races", profile.careerStats.races},
			{"victories", profile.careerStats.victories},
			{"losses", profile.careerStats.losses},
			{"accidents", profile.careerStats.accidents},
			{"creditsEarned", profile.careerStats.creditsEarned},
			{"carBought", profile.careerStats.carBought}
		}},
		{"garage", garage}
	};
}
