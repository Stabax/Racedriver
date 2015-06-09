//Basic_File.cpp

#include "Basic_File.hpp"

Basic_File::Basic_File(std::string const &filePath) : m_filePath(filePath), m_file(nullptr), m_state(state::good)
{
}

Basic_File::~Basic_File()
{
  delete m_file;
  m_file = nullptr;
}

bool Basic_File::exist(std::string const &path)
{
  std::ifstream tmpFile(path.c_str());
  if(tmpFile)
    return true;
  else
    return false;
}

std::string Basic_File::extractDirPath(std::string const &path)
{
  size_t slash = path.find_last_of("/");
  if(slash == std::string::npos)
    return ("");
  else
    return (path.substr(0, slash));
}

Basic_File::state Basic_File::getState() const
{
  return m_state;
}

std::string Basic_File::getPath() const
{
  return m_filePath;
}

void Basic_File::setPath(std::string const &path)
{
  clearState();
  if(m_filePath == "")
    m_filePath = path;
  else
    m_state = state::fail;
}

void Basic_File::clearState()
{
  m_state = state::good;
}

bool Basic_File::isOpen() const
{
  if(m_file == nullptr || ! m_file->is_open())
    return false;
  else
    return true;
}

bool Basic_File::isPathSet() const
{
  if(m_filePath != "")
    return true;
  else
    return false;
}

bool Basic_File::exist()
{
  clearState();
  if(isPathSet())
  {
    return(exist(m_filePath));
  }
  m_state = state::nopath;
  throw(File_Exception("Basic_File::exist()", "no_path"));
}

bool Basic_File::isGood() const
{
  if(m_state == state::good)
    return true;
  return false;
}

std::string Basic_File::extractDirPath()
{
  if(isPathSet())
    return extractDirPath(m_filePath);
  else
  {
    m_state = state::nopath;
    throw(File_Exception("Basic_File::extractDirPath()", "no_path"));
  }
}

void Basic_File::displayState() const
{
  if(m_state == fstate::good)
    std::cout<<"GOOD\n";
  else if(m_state == fstate::badarg)
    std::cout<<"BAD_ARG\n";
  else if(m_state == fstate::open)
    std::cout<<"OPEN: must be close\n";
  else if(m_state == fstate::close)
    std::cout<<"CLOSE: must be open\n";
  else if(m_state == state::nopath)
    std::cout<<"NO_PATH\n";
  else
    std::cout<<"FAIL\n";
}

void Basic_File::create()
{
  clearState();
  if(isPathSet())
  {
    if(! exist())
    {
      if(! dirExist(extractDirPath().c_str()))
        mkPathDir(extractDirPath().c_str(), 0777);
      std::ofstream tmpFile(m_filePath.c_str());
      if(tmpFile)
        ;
      else
        m_state = state::fail;
    }
    else
      m_state = state::fail;
  }
  else
    m_state = state::nopath;
}

void Basic_File::open()
{
  clearState();
  if(! isOpen())
  {
    if(isPathSet())
	  {
	    if(exist())
	    {
	      m_file = new std::fstream();
	      m_file->open(m_filePath.c_str());
	      if(m_file->rdstate() == std::fstream::goodbit)
		      ;
	      else
		    {
		      m_state = state::fail;
		      delete m_file;
		      m_file = nullptr;
		    }
	    }
	    else
	      m_state = state::fail;
	  }
    else
	    m_state = state::nopath;
  }
  else
    m_state = state::open;
}

void Basic_File::close()
{
  clearState();
  if(isOpen())
  {
    m_file->clear();
    m_file->close();
    if(m_file->rdstate() == std::fstream::goodbit)
	  {
	    delete m_file;
	    m_file = nullptr;
	  }
    else
	    m_state = state::fail;
  }
  else
    m_state = state::close;
}

void Basic_File::rename(std::string const &name)
{
  clearState();
  if(! isOpen())
  {
    if(isPathSet())
    {
      if(name.find_first_of("/") == std::string::npos && name != "")
      {
	      std::string path = extractDirPath();
	      if(path != "")
	        path += '/';
        if(exist() && ! exist(path + name))
	      {
	        if(std::rename(m_filePath.c_str(), (path + name).c_str()) == 0)
	          m_filePath = path + name;
	        else
	          m_state = state::fail;
	      }
        else
	        m_state = state::fail;
      }
      else
        m_state = state::badarg;
    }
    else
      m_state = state::nopath;
  }
  else
    m_state = state::open;
}

void Basic_File::move(std::string const &dir)
{
  clearState();
  if(! isOpen())
  {
    if(isPathSet())
	  {
      if(dir.find_last_of("/") != dir.length() - 1)
      {	      
        size_t character = m_filePath.find_last_of("/");
        if(character == std::string::npos)
	        character = 0;
        std::string fileName(m_filePath.substr(character, m_filePath.length()));
        if(exist() && ! exist(dir + '/' + fileName))
	      {
	        if(! dirExist(dir.c_str()))
	          mkPathDir(dir.c_str(), 0777);
	        if(std::rename(m_filePath.c_str(), (dir + '/' + fileName).c_str()) == 0)
	          m_filePath = dir + '/' + fileName;
	        else
	          m_state = state::fail;
	      }
        else
	        m_state = state::fail;
	    }
      else
        m_state = state::badarg;    
	  }
    else
	    m_state = state::nopath;
  }
  else
    m_state = state::open;
}

void Basic_File::remove()
{
  clearState();
  if(! isOpen())
  {
    if(isPathSet())
	  {
	    if(std::remove(m_filePath.c_str()) == 0)
	    {
	      if(m_file != nullptr)
	      {
	        delete m_file;
	        m_file = nullptr;
	      }
	    }
	    else
	      m_state = state::fail;
	  }
    else
	    m_state = state::nopath;
  }
  else
    m_state = state::open;
}
