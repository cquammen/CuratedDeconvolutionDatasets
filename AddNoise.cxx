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
 
  bool noiseSet = false;
  std::string noise;

  bool meanSet      = false;
  double mean       = 0.0;

  bool stdevSet     = false;
  double stdev      = 0.0;

  bool scaleSet     = false;
  double scale      = 1.0;

  if ( !GetArgument( argc, argv, "--input",  true,  inputName,  inputSet  ) ||
       !GetArgument( argc, argv, "--output", true,  outputName, outputSet ) ||
       !GetArgument( argc, argv, "--noise",  true,  noise,      noiseSet  ) ||
       !GetArgument( argc, argv, "--mean",   false, mean,       meanSet   ) ||
       !GetArgument( argc, argv, "--stdev",  false, stdev,      stdevSet  ) ||
       !GetArgument( argc, argv, "--scale",  false, scale,      scaleSet  ) )
    {
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

