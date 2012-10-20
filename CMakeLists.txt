project(CuratedDeconvolutionDatasets)
cmake_minimum_required(VERSION 2.8.5)

find_package( ITK )
include( ${ITK_USE_FILE} )

include_directories(
  ${CuratedDeconvolutionDatasets_SOURCE_DIR}
  ${CuratedDeconvolutionDatasets_SOURCE_DIR}/src
  ${CuratedDeconvolutionDatasets_SOURCE_DIR}/src/itk
)

message(STATUS ${CuratedDeconvolutionDatasets_SRC_DIR}/src/itk )

add_library( Arguments
  src/Arguments.cxx
)

set(EXECUTABLES
  AddNoise
  BlurImage
)

foreach( executable ${EXECUTABLES} )
  add_executable( ${executable}
    ${executable}.cxx
    )
  target_link_libraries( ${executable}
    ${ITK_LIBRARIES}
    Arguments
    )
endforeach()
