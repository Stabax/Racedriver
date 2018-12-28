#include "HeatEngine.hh"
#include "Menu.hh"

HeatEngine::HeatEngine(const json& data)
 : Engine(data), _torque(data["torque"].get<int>())
{

}

HeatEngine::~HeatEngine()
{

}