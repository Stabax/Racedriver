//general_exceptions.hpp

/*
*Ces classes dérivent toutes de std::exception.
*Elles ont pour rôle de pouvoir créer des exceptions spécialisées
*dans chaque type de problème afin de mieux êtres traitées.
*/

#ifndef GENERAL_EXCEPTIONS_H_
#define GENERAL_EXCEPTIONS_H_

#include <exception>
#include <string>


//permet d'envoyer une exception contenant plus d'informations.
class Detailed_Exception : public std::exception
{
public:
  //constructeurs
  Detailed_Exception(std::string const &senderFunction = "unknown", std::string const &reason = "unknown") throw();
  
  //destructeur
  virtual ~Detailed_Exception() throw();
  
  //méthodes
  virtual const char* what() const throw();
  std::string getSenderFunction() const throw();
  std::string getReason() const throw();

protected:
  //attributs
  std::string m_senderFunction;
  std::string m_reason;
};



class File; //on évite l'inclution multiple en incluant l'implementation de File dans Exceptions.cpp.

//Permet de charger le texte de l'exception depuis un fichier.
class Loaded_Exception : public std::exception
{
public:
  //constructeurs
  Loaded_Exception() throw();
  Loaded_Exception(unsigned const &line) throw();
  Loaded_Exception(std::string const &exceptionFilePath, unsigned const &line) throw();
  Loaded_Exception(const Loaded_Exception& other) throw() = delete;
  
  //destructeur
  virtual ~Loaded_Exception() throw();
  
  //méthodes statiques
  static void setExceptionFilePath(std::string const &filePath);
  
  //méthodes
  virtual const char* what() const throw();
  std::string reason() const throw();
  
  //opérateurs
  Loaded_Exception& operator=(const Loaded_Exception& other) throw() = delete;  

protected:
  //attributs
  static std::string systemExceptionFilePath;
  File* m_exceptionFile;
  unsigned m_line;
};



//permet d'envoyer une exception contenant plus d'informations
///en chargeant le texte de l'exception depuis un fichier.
class Detailed_Loaded_Exception : public Loaded_Exception, public Detailed_Exception
{
public:
  //constructeurs
  Detailed_Loaded_Exception() throw();
  Detailed_Loaded_Exception(unsigned const &line) throw();
  Detailed_Loaded_Exception(std::string const &senderFunction) throw();
  Detailed_Loaded_Exception(unsigned const &line, std::string const &senderFunction) throw();
  Detailed_Loaded_Exception(std::string const &exceptionFilePath, unsigned const &line, std::string const &senderFunction) throw();
  
  //destructeur
  virtual ~Detailed_Loaded_Exception() throw();
  
  //méthodes
  virtual const char* what() const throw();
};

#endif //GENERAL_EXCEPTIONS_H_
