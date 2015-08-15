//Basic_File.hpp

/*
*Cette classe est base pour manipuler des fichiers.
*Cette classe permet de controler la création/suppression,
*le nom et l'emplacement des fichiers.
*/

#ifndef BASIC_FILE_H_
#define BASIC_FILE_H_

#include "system_exceptions.hpp"
#include "directory.hpp"
#include <fstream>
#include <iostream>

class Basic_File
{
  //fonctions amies

public:
  enum class state
  {
    good,
    //le fichier est fermé... erreur
    close,
    //le fichier est ouvert ... erreur
    open,
    //mauvais argument envoyé
    badarg,
    //le fichier n'a pas de chemin spécifié
    nopath,
    //autre erreur, la reqête n'a pas aboutie
    fail,
  };

  //constructeurs
  Basic_File(std::string const &filePath = "");
  Basic_File(Basic_File const &OtherFile) = delete;

  //destructeur
  virtual ~Basic_File();

  //méthodes statiques
  static bool exist(std::string const &path);
  static std::string extractDirPath(std::string const &path);

  //accesseurs
  state getState() const;
  std::string getPath() const;

  //mutateurs
  void setPath(std::string const &path);

  //méthodes
protected:
  void clearState();
public:
  bool isOpen() const;
  bool isPathSet() const;
  bool exist();
  bool isGood() const;
  std::string extractDirPath();
  //méthode de debugging:
  void displayState() const;
  void create();
  void open();
  void close();
  void rename(std::string const &name);
  void move(std::string const &dir = "");
  void remove();

  //opérateurs méthodes ( =, (), [], -> )
  Basic_File& operator=(const Basic_File &) = delete;

protected:
  //attributs
  std::string m_filePath;
  std::fstream *m_file;
  state m_state;
};

typedef Basic_File::state fstate;
typedef Basic_File BFile;

//opérateurs non méthodes (+, ++, -, --, +=, -=, /=, *=, %=, +, -, *, /, %, ==, !=, <, >, <=, >=, <<, >> )

#endif //BASIC_FILE_H_
