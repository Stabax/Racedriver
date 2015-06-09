//system_exceptions.cpp

#include "system_exceptions.hpp"

/////////////////////////////////////////////////////////////////////////////

File_Exception::File_Exception() throw() : Detailed_Exception("unknown", "File_Exception")
{
}

File_Exception::File_Exception(std::string const &senderFunction, std::string const &reason) throw() : Detailed_Exception(senderFunction, reason)
{
}

File_Exception::~File_Exception() throw()
{
}

const char* File_Exception::what() const throw()
{
  return ("File_Exception");
}

/////////////////////////////////////////////////////////////////////////////

