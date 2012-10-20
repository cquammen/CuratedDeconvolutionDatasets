#include <iostream>

#include <cstdlib>

// Core ITK classes
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include "Arguments.h"

///////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[] )
{
  // Parse arguments
  bool inputSet = false;
  std::string inputFile;

  bool kernelSet = false;
  std::string kernelFile;

  bool outputSet = false;
  std::string outputFile;
 
  bool normalizeSet = false;
  bool normalize = false;

  std::vector< std::string > boundaryConditionTypes;
  boundaryConditionTypes.push_back( "ZeroFluxNeumann" );
  boundaryConditionTypes.push_back( "Constant" );
  boundaryConditionTypes.push_back( "Periodic" );

  bool boundaryConditionSet     = false;
  std::string boundaryCondition = boundaryConditionTypes[0];


  if ( !GetArgument( argc, argv, "--input",  true, inputFile, inputSet ) ||
       !GetArgument( argc, argv, "--kernel", true, kernelFile, kernelSet ) ||
       !GetArgument( argc, argv, "--output", true, outputFile, outputSet ) ||
       !GetArgument( argc, argv, "--normalize", false, normalize, normalizeSet ) ||
       !GetArgument( argc, argv, "--boundaryCondition",  false,
                     boundaryCondition,  boundaryConditionSet ) )
    {
    return EXIT_FAILURE;
    }

  bool validBoundaryCondition = false;
  for ( size_t i = 0; i < boundaryConditionTypes.size(); ++i )
    {
    if ( boundaryCondition == boundaryConditionTypes[i] )
      {
      validBoundaryCondition = true;
      break;
      }
    }

  return EXIT_SUCCESS;
}
