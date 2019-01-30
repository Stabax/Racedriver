#include "ScriptEngine.hh"
#include "Game.hh"
#include "Menu.hh"
#include "Spoiler.hh"
#include "Engine.hh"
#include "Tires.hh"
#include "Profile.hh"
#include "Race.hh"
#include "cppMenus.hh"

std::map<std::string, std::string> ScriptEngine::scripts = std::map<std::string, std::string>();
std::map<std::string, std::string> ScriptEngine::environment = std::map<std::string, std::string>();

void ScriptEngine::runScript(const std::string &scriptId)
{
  if (scriptId == "") throw (std::runtime_error("No script given"));
  run(scripts[scriptId]);
}

void ScriptEngine::run(const std::string &script)
{
  sol::state lua; // creates a Lua context and loads standard Lua libraries

  exposeCpp(lua);
  exposeCollections(lua);
  try {
    lua.script(script);
  } catch (std::exception &e) {
    Menu::alert("Script error: "+std::string(e.what()));
  }
}
void ScriptEngine::exposeCpp(sol::state &lua)
{
  //General
  lua.set_function("print", [=] (std::string x) { Terminal::get() << x; });
  lua.set_function("clearScreen", [] () { Terminal::get().clearScreen(); });
  lua.set_function("pause", [] () { getch(); });
  lua.set_function("exit", [] () { exit(0); });
  lua.set_function("alert", [=] (std::string msg) { Menu::alert(msg); });
  lua.set_function("goTo", [=] (std::string id) { Menu::goTo(id); });
  lua.set_function("goToPath", [=] (std::string id, std::string path) { Menu::goTo(id, path); });
  lua.set_function("setEnv", [=] (std::string key, std::string value) { environment[key] = value; });
  lua.set_function("getEnv", [=] (std::string key) { return (environment[key]); });
  //Menu helper
  lua.set_function("getInputData", [=] (std::string id) {
    std::shared_ptr<MenuInput> in = std::dynamic_pointer_cast<MenuInput>(Menu::active->getItem(id));
    return (in->getData());
  });
  lua.set_function("setInputData", [=] (std::string id, std::string value) {
    std::shared_ptr<MenuInput> in = std::dynamic_pointer_cast<MenuInput>(Menu::active->getItem(id));
    in->setData(value);
  });
  lua.set_function("getSelectValue", [=] (std::string id) {
    std::shared_ptr<MenuSelect> sel = std::dynamic_pointer_cast<MenuSelect>(Menu::active->getItem(id));
    return (sel->getData());
  });
  lua.set_function("setSelectValue", [=] (std::string id, std::string value) {
    std::shared_ptr<MenuSelect> sel = std::dynamic_pointer_cast<MenuSelect>(Menu::active->getItem(id));
    sel->setData(value);
  });
  //Custom
  lua.set_function("printASCIILogo", [] (int art) { Menu::printASCIILogo(art); });
  lua.set_function("getVersion", [] () { return (GAME_VERSION); });
  //Profile management
  lua.set_function("setProfileName", [=] (std::string name) { Profile::active->rename(name); });
  lua.set_function("setProfileDifficulty", [=] (std::string diff) { Profile::active->difficulty = static_cast<Profile::Difficulty>(atoi(diff.c_str())); });
  lua.set_function("getProfileName", [] () { return (Profile::active->name); });
  lua.set_function("getProfileDifficulty", [] () { return (std::to_string(Profile::active->difficulty)); });
  lua.set_function("loadProfile", [=] (std::string save) { Profile::load(save); });
  lua.set_function("createProfile", [=] (std::string name) { Profile::create(name); });
  //Garage management
  Car::expose(lua);
  lua.set_function("getBox", [=] (std::string index) { return (Profile::active->garage.getBox(atoi(index.c_str()))); });
  //Cpp Menus
  lua.set_function("loadGameMenu", &menuLoadGame);
  lua.set_function("startRace", [] () {
    Race race(std::make_shared<Car>(Profile::active->garage.getBox(atoi(ScriptEngine::environment["Box"].c_str()))),
              Track::collection[(atoi(ScriptEngine::environment["Track"].c_str()))]);
    
    if (race.preparations()) race.start();
  });
  lua.set_function("statsMenu", &menuStats);
  lua.set_function("selectCarMenu", &menuSelectCar);
  lua.set_function("selectTrackMenu", &menuSelectTrack);
  lua.set_function("garageMenu", &menuGarage);
  lua.set_function("buyCarMenu", &menuBuyCar);
  lua.set_function("buyBoxMenu", &menuBuyBox);

  lua.set_function("upgradeEngineMenu", &menuUpgradeEngine);
  lua.set_function("upgradeSpoilerMenu", &menuUpgradeSpoiler);
  lua.set_function("upgradeTiresMenu", &menuUpgradeTires);
  lua.set_function("chooseCharmMenu", &menuChooseCharm);
  //lua.set_function("career", &menuCourse);
  //lua.set_function("freeRace", &menuCourseLibre);
}

void ScriptEngine::exposeCollections(sol::state &lua)
{
  Collection<Engine>::expose(lua);
  lua["Engines"] = Engine::collection;
  Collection<Spoiler>::expose(lua);
  Spoiler::expose(lua);
  lua["Spoilers"] = Spoiler::collection;
  Collection<Tires>::expose(lua);
  lua["Tires"] = Tires::collection;
}

void ScriptEngine::loadScripts(const xml_document &doc)
{
  scripts.clear();
	for (pugi::xml_node el = doc.first_child(); el; el = el.next_sibling())
	{
    if (strcmp(el.name(), "Script") == 0)
    {
      scripts.emplace(el.attribute("Id").value(), el.first_child().value());
    }
	}
}

void ScriptEngine::console(Menu &currentMenu)
{
  int input;
  std::string command;

  Terminal::get().setCursor(1);
  currentMenu.renderConsole(command); //Renders console
  while ((input = getch()) != KEY_F(11))
  {
    Terminal::get().clearScreen();
    if (input == KEY_ENTER || input == '\r' || input == '\n')
    {
      run(command);
      command.clear();
    }
    else if (command.length() > 0 && (input == KEY_BACKSPACE || input == '\b')) command.erase(--command.end());
    else command += input;
    currentMenu.renderConsole(command);
  }
  Terminal::get().setCursor(0);
  Terminal::get().clearScreen();
}