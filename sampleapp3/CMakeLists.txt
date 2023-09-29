cmake_minimum_required(VERSION 3.14)
project(kotobakoe VERSION 0.0.1 LANGUAGES CXX)

# SETS
set(PROJ_NAME "kotobakoe")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXE_PATH ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# OPTIONS
option(USE_DEBUG "Debug mode" ON)
option(USE_LINUX_ENV "Linux mode" ON)

# MODE
if (USE_DEBUG)
    message(STATUS "- DEBUG MODE")
    add_definitions(-DDEBUG)
    set(CMAKE_BUILD_TYPE Debug)
    include(CMakePrintHelpers)
    cmake_print_variables(EXE_PATH)
else()
    message(STATUS "- RELEASE MODE")
    # release
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "EXE_PATH: ${EXE_PATH}")

# OPERATING SYSTEM
if (USE_LINUX_ENV)
    # LINUX
    message(STATUS "- OS LINUX")
    add_compile_options("-std=c++17")
else()
    # WIN
    message(STATUS "- OS WINDOWS")    
    add_compile_options("/std:c++17")
endif()

# EXTERNAL PACKAGE
find_package(spdlog CONFIG REQUIRED)
find_package(lyra CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# INCLUDE
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
# add_subdirectory()

# LIBRARY
# set(<NAME_1> "<SOURCE-PATH>")
# add_library(<NAME> STATIC <SOURCEFILE>)
# target_include_directories(<NAME_FOR_TARGET_LINK_LIBRARIES> PUBLIC <NAME_1>)
# ex: target_link_libraries(EXAMPLE_LIB PUBLIC <NAME_FOR_TARGET_LINK_LIBRARIES>)


# EXECUTABLE FILE
set(SOURCES 
    src/main.cpp
)
add_executable(${PROJ_NAME}
    ${SOURCES}
)
target_include_directories(${PROJ_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/inc
)

## set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# LINK LIBRARIES
target_link_libraries(${PROJ_NAME} PUBLIC 
    spdlog::spdlog spdlog::spdlog_header_only
    bfg::lyra
    nlohmann_json nlohmann_json::nlohmann_json
)

# COMPILE OPTIONS
## surpress warning
target_compile_options(${PROJ_NAME} PUBLIC
       $<$<CXX_COMPILER_ID:MSVC>:/W4 /INCREMENTAL:NO>
       $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall>)
