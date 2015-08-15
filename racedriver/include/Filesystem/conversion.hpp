//conversion.hpp

#ifndef CONVERSION_H_
#define CONVERSION_H_

#include <iomanip>
#include <sstream>

template <typename convertible>
std::string toString(convertible number)
{
  std::ostringstream converter;
  converter << number;
  return converter.str();
}

template <typename returnType>
std::string toNumber(std::string txt)
{
  std::istringstream converter(txt);
  returnType value;
  converter >> value;
  return value;
}

template <typename convertible>
std::string decToHexa(convertible number)
{
  std::ostringstream converter;
  converter << std::setbase(16) << number;
  return converter.str();
}
#endif //CONVERSION_H_
