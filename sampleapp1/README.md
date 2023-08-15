# sampleapp1
This apps goals is to demonstrate how to build static library on linux (.a) and how to consume it on linux environment using  CMake

# my_library build
cd my_library
mkdir build && cd build && cmake ../ && cmake --build . && cp libmy_library.a ../../my_app

# my_app build
cd my_app
mkdir build && cd build && cmake ../ && cmake --build . 

# or use runner shell script
./runner -a