#ifndef SCRIPTENGINE_HH_
#define SCRIPTENGINE_HH_

#include <sol.hpp>
#include "Terminal.hh"

class ScriptEngine
{
public:
  static void run(const std::string &script);
  static void exposeCpp(sol::state &lua);
};



#endif /* !SCRIPTENGINE_HH_ */