#include <iostream>

#include <cstdlib>

#include <itkAdditiveGaussianNoiseImageFilter.h>
#include <itkShotNoiseImageFilter.h>

#include "Arguments.h"

///////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[] )
{
  // Parse arguments
  bool inputSet     = false;
  std::string inputName;

  bool outputSet    = false;
  std::string outputName;
 
  bool noiseTypeSet = false;
  std::string noiseType;

  bool meanSet      = false;
  double mean       = 0.0;

  bool stdevSet     = false;
  double stdev      = 0.0;

  bool scaleSet     = false;
  double scale      = 1.0;

  if ( !GetArgument( argc, argv, "--input", inputName, inputSet ) ||
       !GetArgument( argc, argv, "--output", outputName, outputSet ) ||
       !GetArgument( argc, argv, "--noiseType", noiseType, noiseTypeSet ) ||
       !GetArgument( argc, argv, "--mean", mean, meanSet ) ||
       !GetArgument( argc, argv, "--stdev", stdev, stdevSet ) ||
       !GetArgument( argc, argv, "--scale", scale, scaleSet ) )
    {
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

