#include <iostream>

#include <cstdlib>

// Core ITK classes
#include <itkFFTConvolutionImageFilter.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkConstantBoundaryCondition.h>
#include <itkPeriodicBoundaryCondition.h>
#include <itkZeroFluxNeumannBoundaryCondition.h>

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

  bool constantSet = false;
  double constant = 0.0;

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
                     boundaryCondition,  boundaryConditionSet ) ||
       !GetArgument( argc, argv, "--constant", false,
                     constant, constantSet ) )
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

  // Set up useful typedefs
  typedef double                                      PixelType;
  const unsigned int                                  Dimension = 3;
  typedef itk::Image< PixelType, Dimension >          ImageType;
  typedef itk::ImageFileReader< ImageType >           ReaderType;
  typedef itk::ImageFileWriter< ImageType >           WriterType;
  typedef itk::FFTConvolutionImageFilter< ImageType > ConvolutionType;

  // Read image
  ConvolutionType::BoundaryConditionPointerType bc = NULL;
  try
    {
    ReaderType::Pointer inputReader = ReaderType::New();
    inputReader->SetFileName( inputFile.c_str() );

    ReaderType::Pointer kernelReader = ReaderType::New();
    kernelReader->SetFileName( kernelFile.c_str() );

    // Blur image
    ConvolutionType::Pointer convolutionFilter = ConvolutionType::New();
    convolutionFilter->SetInput( inputReader->GetOutput() );
    convolutionFilter->SetKernelImage( kernelReader->GetOutput() );
    convolutionFilter->SetNormalize( normalize );

    if ( boundaryCondition == boundaryConditionTypes[0] )
      {
      bc = new itk::ZeroFluxNeumannBoundaryCondition< ImageType, ImageType >();
      }
    else if ( boundaryCondition == boundaryConditionTypes[1] )
      {
      itk::ConstantBoundaryCondition< ImageType, ImageType > *cbc = new itk::ConstantBoundaryCondition< ImageType, ImageType >();
      cbc->SetConstant( constant );
      bc = cbc;
      }
    else if ( boundaryCondition == boundaryConditionTypes[2] )
      {
      bc = new itk::PeriodicBoundaryCondition< ImageType, ImageType >();
      }
    else
      {
      std::cerr << "Unknown boundary condition type '" << boundaryCondition << "'." << std::endl;
      return EXIT_FAILURE;
      }
    convolutionFilter->SetBoundaryCondition( bc );

    // Write image
    WriterType::Pointer outputWriter = WriterType::New();
    outputWriter->SetFileName( outputFile.c_str() );
    outputWriter->SetInput( convolutionFilter->GetOutput() );
    outputWriter->Update();
    }
  catch ( itk::ExceptionObject & e )
    {
    std::cerr << "Exception caught" << std::endl;
    std::cerr << e << std::endl;
    }
  delete bc;

  return EXIT_SUCCESS;
}
