#include "Arguments.h"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////
bool GetArgument( int argc, char* argv[], const std::string & name, std::string & value, bool & valueSet )
{
  valueSet = false;
  for ( int i = 0; i < argc; ++i )
    {
    std::string candidateArgument( argv[i] );
    if ( candidateArgument == name )
      {
      if ( i+1 < argc)
        {
        value = std::string( argv[i+1] );
        std::cout << "Argument " << name << " set to '" << value << "'" << std::endl;
        valueSet = true;
        return true;
        }
      else
        {
        std::cerr << "Argument " << name << " requires a string argument" << std::endl;
        return false;
        }
      }
    }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////
bool GetArgument( int argc, char* argv[], const std::string & name, double & value, bool & valueSet )
{
  valueSet = false;
  for ( int i = 0; i < argc; ++i )
    {
    std::string candidateArgument( argv[i] );
    if ( candidateArgument == name )
      {
      if ( i+1 < argc)
        {
        value = atof( argv[i+1] );
        std::cout << "Argument " << name << " set to '" << value << "'" << std::endl;
        valueSet = true;
        return true;
        }
      else
        {
        std::cerr << "Argument " << name << " requires a string argument" << std::endl;
        return false;
        }
      }
    }

  return true;
}