#include <string>
#include <vector>
#include <DataFile.hh>
#include <ScriptEngine.hh>
#include <Menu.hh>
#include "cppMenus.hh"
#include "Profile.hh"
#include "Engine.hh"
#include "Track.hh"

void menuLoadGame()
{
	std::vector<std::string> saves = DataFile::getFolderContents("./Data/Saves/", ".json");
	std::string menu;
	menu += "<Menu>"
  				"  <Text><Lang Id='profile.select'/>:</Text>"
  				"  <Sep/>";
	for (size_t i = 0; i < saves.size(); i++)
	{
		std::string profilename = saves[i].substr(0, saves[i].find(".json"));
		menu += "	<Button Type='Intern' Target='loadProfile(\""+ saves[i] +"\") goToPath(\"Main\", \"./Data/Menus/Main.xml\")'>" + profilename + "</Button>";
	}
  menu += "	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Home'><Lang Id='global.back'/></Button>"
					"</Menu>";
	Menu::goTo("", menu, DataSource::Document);
}

void menuSelectCar()
{
	std::string menu;
	menu += "<Menu>"
  				" <Text><Lang Id='car.select'/>:</Text>"
					" <Sep/>";
	for (size_t i = 0; i < Profile::active->garage.getSize(); i++)
	{
		menu += " <Button Type='Intern' Target='setEnv(\"Box\", \"" + std::to_string(i) + "\") menuSelectCar()'>"
		        "[Box " + std::to_string(i) + "] " +  Profile::active->garage.get(i).manufacturer + " " + Profile::active->garage.get(i).name + "</Button>";
	}
 	menu += " <Sep/>"
	 				"	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Main'><Lang Id='global.back'/></Button>"
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
	        "	<Button Type='Goto' Path='./Data/Menus/Main.xml' Target='Race'><Lang Id='global.back'/></Button>"
					"</Menu>";
	Menu::popUp("", menu, DataSource::Document);
}

void menuBuyBox()
{
	std::string menu;
	menu += "<Menu>"
					" <Text>Vous allez acheter un "+ std::to_string(Profile::active->garage.getBoxCount()+1) +"e Box,"
					" pour " + std::to_string(Profile::active->garage.getBoxCount()*1000) + " credits</Text>"
					" <Sep/>"
					" <Button Type='Intern' Target=''>Oklm</Button>"
					" <Button Type='Intern' Target=''>Cancel</Button>"
					"</Menu>";
	Menu::popUp("", menu, DataSource::Document);
}