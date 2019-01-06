#include "ScriptEngine.hh"

void ScriptEngine::run(const std::string &script)
{
  sol::state lua; // creates a Lua context and loads standard Lua libraries
  exposeCpp(lua);
  lua.script(script);
}

void ScriptEngine::exposeCpp(sol::state &lua)
{
  lua.set_function("print", [=] (std::string x) { Terminal::get() << x; });
  lua.set_function("clearScreen", [] () { Terminal::get().clearScreen(); });
  lua.set_function("pause", [] () { getch(); });
}