cmake_minimum_required(VERSION 3.5)
project(my_library)

# Library sources
set(SOURCES
    src/my_library.cpp
    # src/another_file.cpp
)

# Include directory
set(INCLUDES
    include
)

# Create the static library
add_library(my_library STATIC ${SOURCES})
target_include_directories(my_library PUBLIC ${INCLUDES})
target_compile_options(my_library PRIVATE -g)

# Example executable
# add_executable(example src/another_file.cpp)
# target_link_libraries(example PRIVATE my_library)
