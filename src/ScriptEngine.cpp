#include "ScriptEngine.hh"
#include "Menu.hh"

std::map<std::string, std::string> ScriptEngine::scripts = std::map<std::string, std::string>();

void ScriptEngine::run(const std::string &script)
{
  if (script == "") throw (std::runtime_error("No script given"));
  std::string &src = scripts[script];
  sol::state lua; // creates a Lua context and loads standard Lua libraries

  exposeCpp(lua);
  try {
    lua.script(src);
  } catch (std::exception &e) {
    Menu::error("Script error: "+std::string(e.what()));
  }
}

void ScriptEngine::exposeCpp(sol::state &lua)
{
  lua.set_function("print", [=] (std::string x) { Terminal::get() << x; });
  lua.set_function("clearScreen", [] () { Terminal::get().clearScreen(); });
  lua.set_function("pause", [] () { getch(); });
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