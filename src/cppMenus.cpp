#include "cppMenus.hh"
#include "DataFile.hh"
#include "Profile.hh"
#include "Menu.hh"
#include "Track.hh"
#include <string>
#include <vector>

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
  				" <Text>Select a car:</Text>";
	for (size_t i = 0; i < Profile::active->garage.getSize(); i++)
	{
		menu += " <Button Type='Intern' Target='setEnv(\"Box\", \"" + std::to_string(i) + "\") menuSelectCar()'>" + Profile::active->garage.getBox(i).name + "</Button>";
	}
 	menu += "	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Main'>Back</Button>"
					"</Menu>";
	Menu::popUp("", menu, DataSource::Document);
}

void menuSelectTrack()
{
	std::string menu;
	menu += "<Menu>"
  				" <Text>Select a car:</Text>";
	for (size_t i = 0; i < Track::collection.size(); i++)
	{
		menu += " <Button Type='Intern' Target='setEnv(\"Track\", \"" + std::to_string(i) + "\")'>" + Track::collection[i].name + "</Button>";
	}
 	menu += "	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Race'>Back</Button>"
					"</Menu>";
	Menu::popUp("", menu, DataSource::Document);
}


void menuGarage()
{
	std::string menu;
	menu += "<Menu Title='3'>";
	for (size_t i = 0; i < Profile::active->garage.getSize(); i++)
	{
		menu += " <Button Type='Intern' Target='setEnv(\"Box\", \"" + std::to_string(i) + "\") goToPath(\"Box\", \"./Data/Menus/Main.xml\") '>" + Profile::active->garage.getBox(i).name + "</Button>";
	}
 	menu += "<Button Type='Intern' Target='buyCarMenu()'>Buy new car</Button>"
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
		menu += " <Button Type='Intern' Target='goToPath(\"Garage\", \"./Data/Menus/Main.xml\") '>" + Car::collection[i].name + "</Button>";
	}
 	menu += "	<Button Type='Intern' Target='garageMenu()'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
	//static_cast<std::shared_ptr<MenuButton>>(Menu::active->getItem("BuyCar"))->bind()
}

void menuUpgradeEngine()
{
	std::string menu;
	menu += "<Menu Title='3'>";
	for (size_t i = 0; i < Engine::collection.size(); i++)
	{
		menu += " <Button Type='Intern' Target='goToPath(\"Garage\", \"./Data/Menus/Main.xml\") '>" + Engine::collection[i].name + "</Button>";
	}
 	menu += "	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='UpgradeCar'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
	//static_cast<std::shared_ptr<MenuButton>>(Menu::active->getItem("BuyCar"))->bind()

}
void menuUpgradeSpoiler()
{
	std::string menu;
	menu += "<Menu Title='3'>";
	for (size_t i = 0; i < Spoiler::collection.size(); i++)
	{
		menu += " <Button Type='Intern' Target='goToPath(\"Garage\", \"./Data/Menus/Main.xml\") '>" + Spoiler::collection[i].name + "</Button>";
	}
 	menu += "	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='UpgradeCar'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
	//static_cast<std::shared_ptr<MenuButton>>(Menu::active->getItem("BuyCar"))->bind()
}

void menuUpgradeTires()
{
	std::string menu;
	menu += "<Menu Title='3'>";
	for (size_t i = 0; i < Tires::collection.size(); i++)
	{
		menu += " <Button Type='Intern' Target='goToPath(\"Garage\", \"./Data/Menus/Main.xml\") '>" + Tires::collection[i].name + "</Button>";
	}
 	menu += "	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='UpgradeCar'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
}

void menuChooseCharm()
{
	Menu::alert("not impl!");
}