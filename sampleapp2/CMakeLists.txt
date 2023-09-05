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
# option for demonstrate sample code
option(LYRA_EXAMPLE "build lyra example" ON)
if (LYRA_EXAMPLE)
  add_definitions(-DLYRA_EXAMPLE)
endif()

option(PQXX_EXAMPLE "build pqxx and postgresql example" ON)
if (PQXX_EXAMPLE)
  add_definitions(-DPQXX_EXAMPLE)
endif()

option(SAMBEL_EXAMPLE "build sambel project example" ON)
if (SAMBEL_EXAMPLE)
  add_definitions(-DSAMBEL_EXAMPLE)
endif()

option(LAT1_EXAMPLE "lat1 example" ON)
if (LAT1_EXAMPLE)
  add_definitions(-DLAT1_EXAMPLE)
endif()

option(LAT2_EXAMPLE "lat2 (eigen) example" ON)
if (LAT2_EXAMPLE)
  add_definitions(-DLAT2_EXAMPLE)
endif()

option(SPDLOG_EXAMPLE "spdlog example" ON)
if (SPDLOG_EXAMPLE)
  add_definitions(-DSPDLOG_EXAMPLE)
endif()

option(DEBUG_MODE "Debug mode" ON)
if (DEBUG_MODE)
  add_definitions(-DDEBUG)
  set(CMAKE_BUILD_TYPE Debug)
else() # Release
  set(CMAKE_BUILD_TYPE Release)
endif()

set(LIBRARY_NAME sambelProject)  # Default name for the library built from src/*.cpp

# --------------------------------------------------------------------------------
#                                     Build
# --------------------------------------------------------------------------------
# Compile all sources into a library
find_package(lyra CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(PostgreSQL REQUIRED)
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
  PUBLIC spdlog::spdlog spdlog::spdlog_header_only
  PUBLIC libpqxx::pqxx pq Threads::Threads
  PUBLIC PostgreSQL::PostgreSQL
  PUBLIC bfg::lyra
)

# Set the properties required, e.g. C++ standard used. Apply to library and main
set_target_properties(
  ${LIBRARY_NAME} sambel
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED YES
)
