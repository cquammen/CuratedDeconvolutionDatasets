#ifndef __Arguments_h
#define __Arguments_h

#include <string>

bool GetArgument( int argc, char* argv[], const std::string & name, bool required,
                  std::string & value, bool & valueSet );
bool GetArgument( int argc, char* argv[], const std::string & name, bool required,
                  double & value, bool & valueSet );

#endif

