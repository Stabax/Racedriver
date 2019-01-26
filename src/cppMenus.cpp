#include "cppMenus.hh"
#include "DataFile.hh"
#include "Profile.hh"
#include "Menu.hh"
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
	menu += "<Menu>"
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

void menuFreeRace()
{
	std::string menu;
	menu += "<Menu>"
  				" <Text>Load Profile:</Text>"
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
		menu += " <Button Id='" + std::to_string(i) + "'>" + Profile::active->garage.getBox(i).name + "</Button>";
	}
 	menu += "	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Main'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
}

void menuGarage()
{
	std::string menu;
	menu += "<Menu>";
	for (size_t i = 0; i < Profile::active->garage.getSize(); i++)
	{
		menu += " <Button Id='" + std::to_string(i) + "'>" + Profile::active->garage.getBox(i).name + "</Button>";
	}
 	menu += "<Button Id='BuyCar'>Buy new car</Button>"
	 				"	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Main'>Back</Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
	//static_cast<std::shared_ptr<MenuButton>>(Menu::active->getItem("BuyCar"))->bind()
}