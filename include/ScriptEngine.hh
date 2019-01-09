#ifndef SCRIPTENGINE_HH_
#define SCRIPTENGINE_HH_

#include <map>
#include <sol.hpp>
#include "DataFile.hh"
#include "Terminal.hh"

struct ScriptEngine
{
  static void runScript(const std::string &scriptId);
  static void run(const std::string &script);
  static void exposeCpp(sol::state &lua);

  static void loadScripts(const xml_document &doc);

  static std::map<std::string, std::string> scripts;
};



#endif /* !SCRIPTENGINE_HH_ */