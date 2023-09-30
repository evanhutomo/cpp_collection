# add_executable(hw hw.cpp)


# CMakeLists.txt for the sample/ directory.

# Define the executable target for the hw.cpp file.
add_executable(hw hw.cpp)

# Find the ftxui package using CMake's find_package.
find_package(ftxui REQUIRED)

# Use the imported target provided by find_package.
target_link_libraries(hw 
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)
