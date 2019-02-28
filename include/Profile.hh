#ifndef PROFILE_HH_
#define PROFILE_HH_

#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Garage.hh"

/*!
 * @brief Struct storing player stats
 */
struct Stats {
	int races;
	int victories;
	int losses;
	int accidents;
	int creditsEarned;
	int carBought;

	Stats(int r = 0, int v = 0, int l = 0, int a = 0, int cr = 0, int c = 0)
	{
		races = r;
		victories = v;
		losses = l;
		accidents = a;
		creditsEarned = cr;
		carBought = c;
	}

  static void expose(sol::environment &lua)
  {
    lua.new_usertype<Stats>("Stats",
      // constructor
      sol::constructors<Stats()>(),

      "races", &Stats::races,
      "victories", &Stats::victories,
      "losses", &Stats::losses,
      "accidents", &Stats::accidents,
      "creditsEarned", &Stats::creditsEarned,
      "carBought", &Stats::carBought
    );
  }
};

/*!
 * @brief Player profile. Used to store the GameSave.
 */
class Profile
{
public:

	enum Difficulty {
		Easy = 1,
		Medium,
		Hard
	};

	Profile(const std::string &name, const std::string &locale);
	Profile(const json &data);
	~Profile();

	static void expose(sol::environment &lua);
	static void create(const std::string &name, const std::string &locale);
	static void load(const std::string &save);

	static void saveActive();
	void save();

	static void supprimerProfile(const int& numeroSave);
	static bool compatible(Profile& Player, const int& numeroBox, const char& rangNewPiece);

	bool rename(const std::string &name);
	bool pay(int price);

	static std::shared_ptr<Profile> active;

	std::string name;
	std::string localization;
	Difficulty difficulty;
	int credits;

	Garage garage;

	//Stats
	Stats careerStats;
};

bool operator!=(Profile& Player, Profile& PlayerSaved);

void to_json(json& j, const Profile& garage);

#endif /* !PROFILE_HH_ */
