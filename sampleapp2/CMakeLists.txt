cmake_minimum_required(VERSION 3.14)
project(CPP_BOILERPLATE VERSION 0.0.1 LANGUAGES CXX)

# --------------------------------------------------------------------------------
#                                  Locate files
# --------------------------------------------------------------------------------
set(SOURCES 
  src/sambel.cpp
  src/lat1.cpp
  src/lat2.cpp  
)

# Learn how to add examples and its option from roots
# option(BUILD_NUMCPP_EXAMPLES "Build NumCpp examples" ON)

set(LIBRARY_NAME sambelProject)  # Default name for the library built from src/*.cpp

# Debugging purpose
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-DDEBUG)
# --------------------------------------------------------------------------------
#                                     Build
# --------------------------------------------------------------------------------
# Compile all sources into a library
find_package(Eigen3 REQUIRED)
set(EIGEN3_INCLUDE_DIR "/opt/vcpkg/packages/eigen3_x64-linux/include")

add_library(${LIBRARY_NAME} OBJECT ${SOURCES})

# Lib needs to see header files, and library users must also able to see (PUBLIC)
message(STATUS "Variable value: ${PROJECT_SOURCE_DIR}")
target_include_directories(${LIBRARY_NAME} 
  PUBLIC ${PROJECT_SOURCE_DIR}/inc
  PUBLIC ${EIGEN3_INCLUDE_DIR}
)
message(STATUS "Variable value: ${PROJECT_SOURCE_DIR}")

# An executable for the file app/main.cpp
add_executable(sambel app/main.cpp)
target_link_libraries(sambel 
  PRIVATE ${LIBRARY_NAME}
  PUBLIC Eigen3::Eigen
)

# Set the properties required, e.g. C++ standard used. Apply to library and main
set_target_properties(
  ${LIBRARY_NAME} sambel
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED YES
)
