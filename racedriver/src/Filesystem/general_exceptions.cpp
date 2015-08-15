//general_exceptions.cpp

#include "Filesystem/general_exceptions.hpp"
#include "Filesystem/File.hpp" //cet include est ici pour éviter l'inclusion multiple

/////////////////////////////////////////////////////////////////////////////

Detailed_Exception::Detailed_Exception(std::string const &senderFunction, std::string const &reason) throw() : m_senderFunction(senderFunction), m_reason(reason)
{
}

Detailed_Exception::~Detailed_Exception() throw()
{
}

const char* Detailed_Exception::what() const throw()
{
  return ("Detailed_Exception");
}

std::string Detailed_Exception::getSenderFunction() const throw()
{
  return (m_senderFunction);
}

std::string Detailed_Exception::getReason() const throw()
{
  return (m_reason);
}

/////////////////////////////////////////////////////////////////////////////

Loaded_Exception::Loaded_Exception() throw() : m_exceptionFile(nullptr), m_line(0)
{
}

Loaded_Exception::Loaded_Exception(unsigned const &line) throw() : m_exceptionFile(new File(systemExceptionFilePath)), m_line(line)
{
}

Loaded_Exception::Loaded_Exception(std::string const &exceptionFilePath, unsigned const &line) throw() : m_exceptionFile(new File(exceptionFilePath)), m_line(line)
{
}

Loaded_Exception::~Loaded_Exception() throw()
{
  delete m_exceptionFile;
  m_exceptionFile = nullptr;
}

void Loaded_Exception::setExceptionFilePath(std::string const &filePath)
{
  systemExceptionFilePath = filePath;
}

std::string Loaded_Exception::reason() const throw()
{
  if(!(m_exceptionFile == nullptr) && m_exceptionFile->isPathSet())
  {
    m_exceptionFile->open();
    return (m_exceptionFile->readLine(m_line));
    m_exceptionFile->close();
  }
  else
    return ("unknown");
}

const char* Loaded_Exception::what() const throw()
{
  return ("Loaded_Exception");
}

/////////////////////////////////////////////////////////////////////////////


Detailed_Loaded_Exception::Detailed_Loaded_Exception() throw() : Loaded_Exception(), Detailed_Exception("unknown", reason())
{
}

Detailed_Loaded_Exception::Detailed_Loaded_Exception(unsigned const &line) throw() : Loaded_Exception(line), Detailed_Exception("unknown", reason())
{
}

Detailed_Loaded_Exception::Detailed_Loaded_Exception(std::string const &senderFunction) throw() : Loaded_Exception(), Detailed_Exception(senderFunction, reason())
{
}

Detailed_Loaded_Exception::Detailed_Loaded_Exception(unsigned const &line, std::string const &senderFunction) throw() : Loaded_Exception(line), Detailed_Exception(senderFunction, reason())
{
}

Detailed_Loaded_Exception::Detailed_Loaded_Exception(std::string const &exceptionFilePath, unsigned const &line, std::string const &senderFunction) throw() :Loaded_Exception(exceptionFilePath, line), Detailed_Exception(senderFunction, reason())
{
}

Detailed_Loaded_Exception::~Detailed_Loaded_Exception() throw()
{
  delete m_exceptionFile;
  m_exceptionFile = nullptr;
}

const char* Detailed_Loaded_Exception::what() const throw()
{
  return ("Detailed_Loaded_Exception");
}

/////////////////////////////////////////////////////////////////////////////
