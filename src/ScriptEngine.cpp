#include "ScriptEngine.hh"
#include "Game.hh"
#include "Menu.hh"
#include "Spoiler.hh"
#include "Engine.hh"
#include "Tires.hh"
#include "Profile.hh"
#include "Race.hh"
#include "Localization.hh"
#include "cppMenus.hh"

std::map<std::string, std::string> ScriptEngine::scripts = std::map<std::string, std::string>();
std::map<std::string, std::string> ScriptEngine::environment = std::map<std::string, std::string>();
sol::state ScriptEngine::engine;
sol::environment ScriptEngine::scriptEnv;

void ScriptEngine::init()
{
  engine.open_libraries(sol::lib::base);
}

void ScriptEngine::reset()
{
  scriptEnv = sol::environment(ScriptEngine::engine, sol::create);
  exposeCollections();
  exposeCpp();
  engine.collect_garbage();
}

void ScriptEngine::runScript(const std::string &scriptId)
{
  if (scriptId == "") throw (std::runtime_error("No script given"));
  run(scripts[scriptId]);
}

void ScriptEngine::run(const std::string &script)
{
  try {
    engine.script(script, scriptEnv);
  } catch (std::exception &e) {
    Menu::alert(std::string(e.what()));
  }
}

void ScriptEngine::exposeCpp()
{
  //General
  scriptEnv.set_function("print", [=] (std::string x) { Terminal::windows.at("main") << x; });
  scriptEnv.set_function("tostring", [=] (int x) { return (std::to_string(x)); });
  scriptEnv.set_function("clearScreen", [] () { Terminal::windows.at("main").clearScreen(); });
  scriptEnv.set_function("pause", [] () { getch(); });
  scriptEnv.set_function("exit", [] () { exit(0); });
  scriptEnv.set_function("alert", [=] (std::string msg) { Menu::alert(msg); });
  scriptEnv.set_function("goTo", [=] (std::string id) { Menu::goTo(id); });
  scriptEnv.set_function("goToPath", [=] (std::string id, std::string path) { Menu::goTo(id, path); });
  scriptEnv.set_function("setEnv", [=] (std::string key, std::string value) { environment[key] = value; });
  scriptEnv.set_function("getEnv", [=] (std::string key) { return (environment[key]); });
  scriptEnv.set_function("getEnvInt", [=] (std::string key) { return (atoi(environment[key].c_str())); });
  //Menu helper
  scriptEnv.set_function("addMenuItem", [=] (int idx, std::string xml) {
    MenuFile menu(xml, DataSource::Document);

    if (!menu.load()) Menu::alert("Invalid XML injection");
    Menu::active->addItem(menu.getData().first_child(), idx);
  });
  scriptEnv.set_function("getCursor", [] () { return (Menu::active->getCursor()); });
  scriptEnv.set_function("getInputData", [=] (std::string id) {
    std::shared_ptr<MenuInput> in = std::dynamic_pointer_cast<MenuInput>(Menu::active->getItem(id));
    return (in->getData());
  });
  scriptEnv.set_function("setInputData", [=] (std::string id, std::string value) {
    std::shared_ptr<MenuInput> in = std::dynamic_pointer_cast<MenuInput>(Menu::active->getItem(id));
    in->setData(value);
  });
  scriptEnv.set_function("getSelectValue", [=] (std::string id) {
    std::shared_ptr<MenuSelect> sel = std::dynamic_pointer_cast<MenuSelect>(Menu::active->getItem(id));
    return (sel->getData());
  });
  scriptEnv.set_function("setSelectValue", [=] (std::string id, std::string value) {
    std::shared_ptr<MenuSelect> sel = std::dynamic_pointer_cast<MenuSelect>(Menu::active->getItem(id));
    sel->setData(value);
  });
  //Custom
  scriptEnv.set_function("printASCIILogo", [] (std::string art) { Menu::printASCIILogo(Menu::convertASCIILogo(art)); });
  scriptEnv.set_function("getVersion", [] () { return (GAME_VERSION); });
  //Profile management
  scriptEnv.set_function("setProfileName", [=] (std::string name) { Profile::active->rename(name); });
  scriptEnv.set_function("setProfileDifficulty", [=] (std::string diff) { Profile::active->difficulty = static_cast<Profile::Difficulty>(atoi(diff.c_str())); });
  scriptEnv.set_function("setProfileLocale", [=] (std::string locale) {
    Profile::active->localization = locale;
    Localization::load(Profile::active->localization);
  });
  //Profile bindings
  scriptEnv.set_function("loadProfile", [=] (std::string save) { Profile::load(save); });
  scriptEnv.set_function("createProfile", [=] (std::string name, std::string locale) { Profile::create(name, locale); });
  if (Profile::active != nullptr)
  {
    scriptEnv["Garage"] = Profile::active->garage;
    scriptEnv.set_function("getProfileName", [] () { return (Profile::active->name); });
    scriptEnv.set_function("getProfileStats", [] () { return (Profile::active->careerStats); });
    scriptEnv.set_function("getProfileDifficulty", [] () { return (std::to_string(Profile::active->difficulty)); });
    scriptEnv.set_function("getProfileLocale", [=] () { return (Profile::active->localization); });
  }
  //Cpp Menus
  scriptEnv.set_function("loadGameMenu", &menuLoadGame);
  scriptEnv.set_function("startRace", [] () {
    Race race(std::make_shared<Car>(Profile::active->garage.get(atoi(ScriptEngine::environment["Box"].c_str()))),
              Track::collection[(atoi(ScriptEngine::environment["Track"].c_str()))]);

    if (race.preparations()) race.start();
  });
  scriptEnv.set_function("statsMenu", &menuStats);
  scriptEnv.set_function("selectCarMenu", &menuSelectCar);
  scriptEnv.set_function("selectTrackMenu", &menuSelectTrack);
  scriptEnv.set_function("buyCarMenu", &menuBuyCar);
  scriptEnv.set_function("buyBoxMenu", &menuBuyBox);
}

void ScriptEngine::exposeCollections()
{
  Stats::expose(scriptEnv);
  Car::expose(scriptEnv);
  Garage::expose(scriptEnv);
  Engine::expose(scriptEnv);
  Spoiler::expose(scriptEnv);
  Tires::expose(scriptEnv);
  Collection<Car>::expose(scriptEnv);
  Collection<Engine>::expose(scriptEnv);
  Collection<Spoiler>::expose(scriptEnv);
  Collection<Tires>::expose(scriptEnv);
  scriptEnv["Cars"] = Car::collection;
  scriptEnv["Engines"] = Engine::collection;
  scriptEnv["Spoilers"] = Spoiler::collection;
  scriptEnv["Tires"] = Tires::collection;
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
  Terminal &term = Terminal::windows.at("main");
  int input;
  std::string command;

  term.setCursor(1);
  currentMenu.renderConsole(command); //Renders console
  while ((input = getch()) != KEY_F(11))
  {
    term.clearScreen();
    if (input == KEY_ENTER || input == '\r' || input == '\n')
    {
      run(command);
      command.clear();
    }
    else if (command.length() > 0 && (input == KEY_BACKSPACE || input == '\b')) command.erase(--command.end());
    else command += input;
    currentMenu.renderConsole(command);
  }
  term.setCursor(0);
  term.clearScreen();
}