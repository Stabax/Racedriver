//system_exceptions.hpp

/*
*Ces classes héritent toutes de std::exception et des classes
*contenues dans general_exceptions.hpp
*Les classes ici présenes sont des classes spécialisées
*qui sont envoyées par tout ce qui représente le systeme
*(code général réutilisable partout, non spécifique au programme actuel)
*/

#ifndef SYSTEM_EXCEPTIONS_H_
#define SYSTEM_EXCEPTIONS_H_

#include "general_exceptions.hpp"

class File_Exception : public Detailed_Exception
{
public:
  File_Exception() throw();
  File_Exception(std::string const &reason, std::string const &senderFunction) throw();
  virtual ~File_Exception() throw();
  virtual const char* what() const throw();
};

#endif //SYSTEM_EXCEPTIONS_H_
