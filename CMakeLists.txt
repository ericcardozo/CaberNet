cmake_minimum_required(VERSION 3.22)
project(cabernet CXX)

include(GNUInstallDirs) # Reasonable Defaults

option(CABERNET_BUILD_EXAMPLES "Build and run the examples demonstration important features" OFF)

# Define source and header file variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(HEADERS
    ${INCLUDE_DIR}/CaberNet.h
    ${INCLUDE_DIR}/CaberNet/tensor.h
    ${INCLUDE_DIR}/CaberNet/tensor/tensor_float.h
    ${INCLUDE_DIR}/CaberNet/tensor/tensor_int.h
    ${INCLUDE_DIR}/CaberNet/functions.h
    ${INCLUDE_DIR}/CaberNet/layers.h
    ${INCLUDE_DIR}/CaberNet/model.h
    ${INCLUDE_DIR}/CaberNet/optimizers.h
    ${INCLUDE_DIR}/CaberNet/criterions.h
    ${INCLUDE_DIR}/CaberNet/dataset.h
    )

set(SOURCES
    ${SOURCE_DIR}/tensor.cpp
    ${SOURCE_DIR}/tensor/tensor_float.cpp
    ${SOURCE_DIR}/tensor/tensor_int.cpp
    ${SOURCE_DIR}/functions.cpp
    ${SOURCE_DIR}/optimizers.cpp
    ${SOURCE_DIR}/layers.cpp
    ${SOURCE_DIR}/criterions.cpp
    ${SOURCE_DIR}/internals/operations/internal_operation_addition.cpp
    ${SOURCE_DIR}/internals/operations/internal_operation_multiplication.cpp
    ${SOURCE_DIR}/internals/operations/internal_operation_matmul.cpp
    ${SOURCE_DIR}/internals/functions/internal_function_linear.cpp
    ${SOURCE_DIR}/internals/functions/internal_function_softmax.cpp
    ${SOURCE_DIR}/internals/functions/internal_function_logsoftmax.cpp
    ${SOURCE_DIR}/internals/functions/internal_function_relu.cpp
    ${SOURCE_DIR}/internals/criterions/internal_criterion_nllloss.cpp
)

find_package(Eigen3 REQUIRED CONFIG)

# Create the library target
add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${INCLUDE_DIR}> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE $<BUILD_INTERFACE:${SOURCE_DIR}>)
target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Install the library and header files
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
add_subdirectory(cmake)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

if(CABERNET_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
