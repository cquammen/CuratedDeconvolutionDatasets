#include <iostream>

#include <cstdlib>

// Core ITK classes
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

// Noise classes
#include <itkAdditiveGaussianNoiseImageFilter.h>
#include <itkShotNoiseImageFilter.h>

#include "Arguments.h"

///////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[] )
{
  // Parse arguments
  bool inputSet     = false;
  std::string inputFile;

  bool outputSet    = false;
  std::string outputFile;
 
  bool noiseSet = false;
  std::string noise;

  bool meanSet      = false;
  double mean       = 0.0;

  bool stdevSet     = false;
  double stdev      = 0.0;

  bool scaleSet     = false;
  double scale      = 1.0;

  if ( !GetArgument( argc, argv, "--input",  true,  inputFile,  inputSet  ) ||
       !GetArgument( argc, argv, "--output", true,  outputFile, outputSet ) ||
       !GetArgument( argc, argv, "--noise",  true,  noise,      noiseSet  ) ||
       !GetArgument( argc, argv, "--mean",   false, mean,       meanSet   ) ||
       !GetArgument( argc, argv, "--stdev",  false, stdev,      stdevSet  ) ||
       !GetArgument( argc, argv, "--scale",  false, scale,      scaleSet  ) )
    {
    return EXIT_FAILURE;
    }

  // Check noise argument for validity
  if ( noise != "Poisson" && noise != "Gaussian" )
    {
    std::cerr << "--noise argument must be 'Poisson' or 'Gaussian'."
              << "It was '" << noise << "'." << std::endl;
    return EXIT_FAILURE;
    }

  // Set up useful typedefs
  typedef double                              PixelType;
  const unsigned int                          Dimension = 3;
  typedef itk::Image< PixelType, Dimension >  ImageType;
  typedef itk::ImageFileReader< ImageType >   ReaderType;
  typedef itk::ImageFileWriter< ImageType >   WriterType;

  // Read input image
  try
    {
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( inputFile.c_str() );

    // Add noise


    // Write output image
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName( outputFile.c_str() );
    writer->SetInput( reader->GetOutput() );
    writer->Update();
    }
  catch ( itk::ExceptionObject & e )
    {
    std::cerr << "Exception caught" << std::endl;
    std::cerr << e << std::endl;
    }

  return EXIT_SUCCESS;
}

