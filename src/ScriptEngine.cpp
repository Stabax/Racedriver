#include "ScriptEngine.hh"
#include "Game.hh"
#include "Menu.hh"
#include "Spoiler.hh"
#include "Engine.hh"
#include "Tires.hh"

std::map<std::string, std::string> ScriptEngine::scripts = std::map<std::string, std::string>();

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
    Menu::error("Script error: "+std::string(e.what()));
  }
}
void ScriptEngine::exposeCpp(sol::state &lua)
{
  lua.set_function("print", [=] (std::string x) { Terminal::get() << x; });
  lua.set_function("clearScreen", [] () { Terminal::get().clearScreen(); });
  lua.set_function("pause", [] () { getch(); });
  lua.set_function("printLogo", [] () { Game::printASCIILogo(); });
  lua.set_function("getInputData", [=] (std::string id) {
    std::shared_ptr<MenuInput> in = std::dynamic_pointer_cast<MenuInput>(Menu::active->getItem(id));
    return (in != nullptr ? in->getData() : "");
  });
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