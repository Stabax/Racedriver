#include <string>
#include <vector>
#include "cppMenus.hh"
#include "DataFile.hh"
#include "Profile.hh"
#include "Menu.hh"
#include "Engine.hh"
#include "Track.hh"
#include "ScriptEngine.hh"

void menuLoadGame()
{
	std::vector<std::string> saves = DataFile::getFolderContents("./Data/Saves/", ".json");
	std::string menu;
	menu += "<Menu>"
  				"  <Text>Load Profile:</Text>";
	for (size_t i = 0; i < saves.size(); i++)
	{
		menu += "	<Button Type='Intern' Target='loadProfile(\""+ saves[i] +"\") goToPath(\"Main\", \"./Data/Menus/Main.xml\")'>" + saves[i] + "</Button>";
	}
  menu += "	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Home'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
}

void menuStats()
{
	std::string menu;
	std::string wlratio = std::to_string(Profile::active->careerStats.victories/(1+Profile::active->careerStats.losses));
	menu += "<Menu Title='4'>"
					" <Text>Stats du Profile: " + Profile::active->name + "</Text>"
					" <Sep/>"
					" <Text> |Courses effectuees: " + std::to_string(Profile::active->careerStats.races) + "</Text>"
					" <Text> |</Text>"
					" <Text> |Victoires: " + std::to_string(Profile::active->careerStats.victories) + "</Text>"
					" <Text> |Defaites: " + std::to_string(Profile::active->careerStats.losses) + "</Text>"
					" <Text> |[V/D Ratio: " + wlratio + "]</Text>"
					" <Text> |</Text>"
					" <Text> |Accidents: " + std::to_string(Profile::active->careerStats.accidents) + "</Text>"
					" <Text>#Stats Carriere:</Text>"
					" <Text> |Credits remportes: " + std::to_string(Profile::active->careerStats.creditsEarned) + "c</Text>"
					" <Text> |</Text>"
					" <Text> |Cars achetees: " + std::to_string(Profile::active->careerStats.carBought) + "</Text>"
					" <Sep/>"
					"	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Main'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
}

void menuSelectCar()
{
	std::string menu;
	menu += "<Menu>"
  				" <Text>Select a car:</Text>"
					" <Sep/>";
	for (size_t i = 0; i < Profile::active->garage.getSize(); i++)
	{
		menu += " <Button Type='Intern' Target='setEnv(\"Box\", \"" + std::to_string(i) + "\") menuSelectCar()'>"
		        "[Box " + std::to_string(i) + "] " +  Profile::active->garage.getBox(i).manufacturer + " " + Profile::active->garage.getBox(i).name + "</Button>";
	}
 	menu += " <Sep/>"
	 				"	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Main'>Back</Button>"
					"</Menu>";
	Menu::popUp("", menu, DataSource::Document);
}

void menuSelectTrack()
{
	std::string menu;
	menu += "<Menu>"
  				" <Text>Select a track:</Text>"
  				" <Sep/>";
	for (size_t i = 0; i < Track::collection.size(); i++)
	{
		menu += " <Button Type='Intern' Target='setEnv(\"Track\", \"" + std::to_string(i) + "\")'>" + Track::collection[i].name + "</Button>";
	}
 	menu += " <Sep/>"
	        "	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Race'>Back</Button>"
					"</Menu>";
	Menu::popUp("", menu, DataSource::Document);
}


void menuGarage()
{
	std::string menu;
	menu += "<Menu Title='3'>";
	for (size_t i = 0; i < Profile::active->garage.getSize(); i++)
	{
		menu += " <Button Type='Intern' Target='setEnv(\"Box\", \"" + std::to_string(i) + "\") goToPath(\"Box\", \"./Data/Menus/Main.xml\") '>"
				  	"[Box " + std::to_string(i) + "] " +  Profile::active->garage.getBox(i).manufacturer + " " + Profile::active->garage.getBox(i).name + "</Button>";
	}
 	menu += " <Sep/>"
	 				" <Button Type='Intern' Target='buyCarMenu()'>Buy new car</Button>"
	 				" <Sep/>"
	 				"	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Main'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
	//static_cast<std::shared_ptr<MenuButton>>(Menu::active->getItem("BuyCar"))->bind()
}

void menuBuyCar()
{
	std::string menu;
	menu += "<Menu Title='3'>";
	for (size_t i = 0; i < Car::collection.size(); i++)
	{
		menu += " <Button Type='Intern' Target='goToPath(\"Garage\", \"./Data/Menus/Main.xml\") '>"
		       + Car::collection[i].manufacturer + " " + Car::collection[i].name + "</Button>";
	}
 	menu += " <Sep/>"
	 				"	<Button Type='Intern' Target='garageMenu()'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
	//static_cast<std::shared_ptr<MenuButton>>(Menu::active->getItem("BuyCar"))->bind()
}

void menuUpgradeEngine()
{
	Car &car = Profile::active->garage.getBox(atoi(ScriptEngine::environment["Box"].c_str()));
	std::vector<Engine> items = Engine::collection.filter([&] (const Engine &e) {
		return (e.manufacturer == car.manufacturer);
	});
	std::string menu;
	menu += "<Menu Title='3'>"
					" <Text>Current: " + car.getEngine()->name + "</Text>"
					" <Text>Power: " + std::to_string(car.getEngine()->mPower.count()) + "ch at " + std::to_string(car.getEngine()->mRevolutions.count()) + "rpm</Text>"
					" <Text>Energy: " + EnergyNames[car.getEngine()->energy] + "</Text>"
					" <Sep/>";
	for (size_t i = 0; i < items.size(); i++)
	{
		menu += " <Button Type='Intern' Target='goToPath(\"Garage\", \"./Data/Menus/Main.xml\") '>" + items[i].name + "</Button>";
	}
 	menu += " <Sep/>"
	 				"	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='UpgradeCar'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
	//static_cast<std::shared_ptr<MenuButton>>(Menu::active->getItem("BuyCar"))->bind()

}
void menuUpgradeSpoiler()
{
	Car &car = Profile::active->garage.getBox(atoi(ScriptEngine::environment["Box"].c_str()));
	std::string menu;
	menu += "<Menu Title='3'>"
					" <Text>Current: " + (car.getSpoiler() == nullptr ? "None" : car.getSpoiler()->manufacturer + " " + car.getSpoiler()->name) + "</Text>"
					" <Text>Aerodynamic: " + (car.getSpoiler() == nullptr ? "N/A" : std::to_string(car.getSpoiler()->getAerodynamic())) + "</Text>"
					" <Sep/>";
	for (size_t i = 0; i < Spoiler::collection.size(); i++)
	{
		menu += " <Button Type='Intern' Target='goToPath(\"Garage\", \"./Data/Menus/Main.xml\") '>"
		      + Spoiler::collection[i].manufacturer + " " + Spoiler::collection[i].name + "</Button>";
	}
 	menu += " <Sep/>"
	 				"	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='UpgradeCar'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
	//static_cast<std::shared_ptr<MenuButton>>(Menu::active->getItem("BuyCar"))->bind()
}

void menuUpgradeTires()
{
	Car &car = Profile::active->garage.getBox(atoi(ScriptEngine::environment["Box"].c_str()));
	std::string menu;
	menu += "<Menu Title='3'>";
					" <Text>Current: " + car.getTires()->manufacturer + " " + car.getTires()->name + "</Text>"
					" <Text>Radius: " + std::to_string(car.getTires()->radius.count()) + "</Text>";
	for (size_t i = 0; i < Tires::collection.size(); i++)
	{
		menu += " <Button Type='Intern' Target='goToPath(\"Garage\", \"./Data/Menus/Main.xml\") '>"
				  + Tires::collection[i].manufacturer + " " + Tires::collection[i].name + "</Button>";
	}
 	menu += " <Sep/>"
	 				"	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='UpgradeCar'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
}

void menuChooseCharm()
{
	Menu::alert("not impl!");
}