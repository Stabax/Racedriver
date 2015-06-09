//directory.hpp

/*
*Ce header définie les fonctions de
*création / suppression de dossiers
*selon le systeme (POSIX ou windows)
*(les dossiers doivent être vides
*pour être supprimés)
*/

#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include <string>

#if defined (_WIN16) || defined (_WIN32) || defined (_WIN64) //si on est sur windows

#include <direct.h>
//int _mkdir(const char* pathname);
//int _rmdir(const char* pathname);
//int _chdir( const char* path);
//char* _getcwd(char* path, int pathSize);

//Pour que ces fonctions soient les mêmes sur tous les OS
#define rmdir(path) _rmdir(path)
#define chdir(path) _chdir(path)
#define getcwd(path, pathSize) _getcwd(path, pathSize)
#define mkdir(path, mode) _mkdir(path) //il n'y a pas de permissions sous windows

//sur windows, les chemins ont une taille limitée
#if defined (_WIN16)
#define MAX_PATH 256
#elif defined (_WIN32) || defined (_WIN64)
#define MAX_PATH 32768
#endif //defined (_WIN16)

inline char* get_current_dir_name() //retourne le chemin absolu du répertoire courrant
{
  return (_getcwd(nullptr, MAX_PATH));
}

#else //si on est sur POSIX

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
//int mkdir(const char *pathname, unsigned mode); //mode est le niveau de permission du dossier, sous forme octale
//int rmdir(const char *pathname);
//char* get_current_dir_name(); //retourne le chemin absolu du répertoire courrant
//int chdir(const char *path); //change le répertoire courrant, retourne -1 si le dossier n'existe pas ou si les permissions ne sont pas bonnes
//int chmod(const char *path, unsigned mode); //change les permissions du fichier/répertoire

#endif //defined (_WIN16) || defined (_WIN32) || defined (_WIN64)

inline bool dirExist(const char* path) //retourne false si le répertoire n'existe pas ou que les droits ne sont pas bons
{
  bool exist;
  char* currentDir = get_current_dir_name();
  if(chdir(path) == 0)
    exist = true;
  else
    exist = false;
  if(chdir(currentDir) == 0)
    return (exist);
  throw (std::string ("Unable to go to the working directory: dirExist()"));
}

template <typename type = std::string> //std::string ou char* ?
inline type firstDir(const std::string path)
{
  if(path.find_first_of("/\\") != std::string::npos)
  {
    return (path.substr(0, path.find_first_of("/\\")).c_str());
  }
  return (nullptr);
}

inline void mkPathDir(const char* path, unsigned mode) //crée tout les dossiers du path (mkdir ne crée que le premier)
{
  std::string path2(path);
  std::string toCreate(""); 
  while(path2.find_first_of("/\\") != std::string::npos)
  {
    toCreate += firstDir(path2);
    if(! dirExist(toCreate.c_str()))
      mkdir(toCreate.c_str(), mode);
    path2 = path2.substr(path2.find_first_of("/\\") + 1, path2.size());
    toCreate += '/';
  }
  mkdir(path, mode);
}

#define currentDirPath() get_current_dir_name() //retourne le chemin absolu du répertoire

#endif //DIRECTORY_H_

/*les modes pour POSIX:
*3 chiffres
*u g o (user group other)
*doit commencer par un 0 (exemple: 0744)
*0 = aucun droit
*1 = execution, 2 = écriture, 3 = execution + écriture 
*4 = lecture, 5 = execution + lecture, 6 = lecture + écriture
*7 = tout les droits
*/

