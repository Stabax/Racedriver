//Profiles.cpp
#include "Profile.hh"
#include <Menu.hh>
#include <Localization.hh>

std::shared_ptr<Profile> Profile::active = nullptr;

Profile::Profile(const std::string &name, const std::string &locale)
 : name(name), localization(locale), difficulty(Difficulty::Easy), credits(10000), garage()
{
	garage.addCar(Car::collection[0]);
}


Profile::Profile(const json &data)
 : name(data["name"].get<std::string>()), localization(data.find("localization") != data.end() ? data["localization"].get<std::string>() : "en-US"),
   difficulty(data["difficulty"].get<Difficulty>()), credits(data["credits"].get<int>()), garage(data["garage"])
{

}

Profile::~Profile()
{
}

void Profile::expose(sol::environment &lua)
{
	lua.new_usertype<Profile>("Profile",
		// constructor
		sol::constructors<Profile(const json &data), Profile(const std::string &name, const std::string &locale)>(),

		"rename", &Profile::rename,

		"name", &Profile::name,
		"difficulty", &Profile::difficulty,
		"localization", &Profile::localization,
		"stats", &Profile::careerStats
	);
}

void Profile::create(const std::string &name, const std::string &locale)
{
	Profile::active = std::make_shared<Profile>(name, locale);
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
		Localization::load(Profile::active->localization);
	} catch (std::exception &e) {
		throw std::runtime_error("Corrupted profile data:"+std::string(e.what()));
	}
}

void Profile::saveActive()
{
	Profile::active->save();
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

void Profile::supprimerProfile([[maybe_unused]]const int& numeroSave)
{
	//Not implemented
}

bool Profile::rename(const std::string &n)
{
	if (n == name) return (true);
	if (!DataFile::erase("./Data/Saves/"+name+".json")) throw (std::runtime_error("Could not delete profile:"+std::string(strerror(errno))));
	name = n;
	save();
	return (true);
}

bool Profile::pay(int price)
{
	if(price > credits)
	{
		Menu::alert("Not enough credits !");
		return (false);
	}
	credits -= price;
	return (true);
}

void to_json(json& j, const Profile& profile) {
	json garage = profile.garage;
	j = {
		{"name", profile.name},
		{"localization", profile.localization},
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
