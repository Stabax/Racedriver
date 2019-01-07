#include "ScriptEngine.hh"

std::map<std::string, std::string> ScriptEngine::_scripts = std::map<std::string, std::string>();

void ScriptEngine::run(const std::string &script)
{
  sol::state lua; // creates a Lua context and loads standard Lua libraries
  exposeCpp(lua);
  lua.script(_scripts[script]);
}

void ScriptEngine::exposeCpp(sol::state &lua)
{
  lua.set_function("print", [=] (std::string x) { Terminal::get() << x; });
  lua.set_function("clearScreen", [] () { Terminal::get().clearScreen(); });
  lua.set_function("pause", [] () { getch(); });
}

void ScriptEngine::loadScripts(const xml_document &doc)
{
  _scripts.clear();
	for (pugi::xml_node el = doc.first_child(); el; el = el.next_sibling())
	{
    if (strcmp(el.name(), "Script") == 0)
    {
      _scripts.emplace(el.attribute("Id").value(), el.first_child().value());
    }
	}
}