#include <iostream>

#include <cstdlib>

// Core ITK classes
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkConstantBoundaryCondition.h>
#include <itkPeriodicBoundaryCondition.h>
#include <itkZeroFluxNeumannBoundaryCondition.h>

// Deconvolution ITK classes
#include <itkInverseDeconvolutionImageFilter.h>
#include <itkLandweberDeconvolutionImageFilter.h>
#include <itkProjectedLandweberDeconvolutionImageFilter.h>
#include <itkRichardsonLucyDeconvolutionImageFilter.h>
#include <itkTikhonovDeconvolutionImageFilter.h>
#include <itkWienerDeconvolutionImageFilter.h>

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

  std::vector< std::string > algorithms;
  algorithms.push_back( "Inverse" );
  algorithms.push_back( "Landweber" );
  algorithms.push_back( "ProjectedLandweber" );
  algorithms.push_back( "RichardsonLucy" );
  algorithms.push_back( "Tikhonov" );
  algorithms.push_back( "Wiener" );

  bool algorithmSet = false;
  std::string algorithm;

  bool kernelZeroMagnitudeThresholdSet = false;
  double kernelZeroMagnitudeThreshold = 0.0;

  bool alphaSet = false;
  double alpha = 0.0;

  bool numberOfIterationsSet = false;
  int numberOfIterations = 1;

  bool regularizationConstantSet = false;
  double regularizationConstant = 0.0;

  bool noiseVarianceSet = false;
  double noiseVariance = 0.0;

  if ( !GetArgument( argc, argv, "--input",  true, inputFile, inputSet ) ||
       !GetArgument( argc, argv, "--kernel", true, kernelFile, kernelSet ) ||
       !GetArgument( argc, argv, "--output", true, outputFile, outputSet ) ||
       !GetArgument( argc, argv, "--normalize", false, normalize, normalizeSet ) ||
       !GetArgument( argc, argv, "--boundaryCondition",  false,
                     boundaryCondition,  boundaryConditionSet ) ||
       !GetArgument( argc, argv, "--constant", false,
                     constant, constantSet ) ||
       !GetArgument( argc, argv, "--algorithm", false, algorithm, algorithmSet ) ||
       !GetArgument( argc, argv, "--kernelZeroMagnitudeThreshold", false,
                     kernelZeroMagnitudeThreshold, kernelZeroMagnitudeThresholdSet ) ||
       !GetArgument( argc, argv, "--alpha", false, alpha, alphaSet ) ||
       !GetArgument( argc, argv, "--numberOfIterations", false,
                     numberOfIterations, numberOfIterationsSet ) ||
       !GetArgument( argc, argv, "--regularizationConstant", false,
                     regularizationConstant, regularizationConstantSet ) ||
       !GetArgument( argc, argv, "--noiseVariance", false,
                     noiseVariance, noiseVarianceSet ) )
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
    
    ConvolutionType::Pointer deconvolutionFilter;

    // Deconvolve image
    if ( algorithm == algorithms[0] )
      {
      typedef itk::InverseDeconvolutionImageFilter< ImageType > FilterType;
      FilterType::Pointer filter = FilterType::New();
      filter->SetKernelZeroMagnitudeThreshold( kernelZeroMagnitudeThreshold );
      deconvolutionFilter = filter;
      }
    else if ( algorithm == algorithms[1] )
      {
      typedef itk::LandweberDeconvolutionImageFilter< ImageType > FilterType;
      FilterType::Pointer filter = FilterType::New();
      filter->SetAlpha( alpha );
      filter->SetNumberOfIterations( numberOfIterations );
      deconvolutionFilter = filter;
      }
    else if ( algorithm == algorithms[2] )
      {
      typedef itk::ProjectedLandweberDeconvolutionImageFilter< ImageType > FilterType;
      FilterType::Pointer filter = FilterType::New();
      filter->SetAlpha( alpha );
      filter->SetNumberOfIterations( numberOfIterations );
      deconvolutionFilter = filter;
      }
    else if ( algorithm == algorithms[3] )
      {
      typedef itk::RichardsonLucyDeconvolutionImageFilter< ImageType > FilterType;
      FilterType::Pointer filter = FilterType::New();
      filter->SetNumberOfIterations( numberOfIterations );
      deconvolutionFilter = filter;
      }
    else if ( algorithm == algorithms[4] )
      {
      typedef itk::TikhonovDeconvolutionImageFilter< ImageType > FilterType;
      FilterType::Pointer filter = FilterType::New();
      filter->SetRegularizationConstant( regularizationConstant );
      deconvolutionFilter = filter;
      }
    else if ( algorithm == algorithms[5] )
      {
      typedef itk::WienerDeconvolutionImageFilter< ImageType > FilterType;
      FilterType::Pointer filter = FilterType::New();
      filter->SetNoiseVariance( noiseVariance );
      deconvolutionFilter = filter;
      }
    else
      {
      std::cerr << "Unknown deconvolution algorithm type '" << algorithm << "'." << std::endl;
      std::cerr << "Should be one of ";
      for ( size_t i = 0; i < algorithms.size(); ++i )
        {
        std::cerr << algorithms[i];
        if ( i < algorithms.size()-1 )
          std::cerr << ", ";
        else
          std::cerr << ".";
        }
      return EXIT_FAILURE;
      }

    deconvolutionFilter->SetInput( inputReader->GetOutput() );
    deconvolutionFilter->SetKernelImage( kernelReader->GetOutput() );
    deconvolutionFilter->SetNormalize( normalize );

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
    deconvolutionFilter->SetBoundaryCondition( bc );

    // Write image
    WriterType::Pointer outputWriter = WriterType::New();
    outputWriter->SetFileName( outputFile.c_str() );
    outputWriter->SetInput( deconvolutionFilter->GetOutput() );
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
