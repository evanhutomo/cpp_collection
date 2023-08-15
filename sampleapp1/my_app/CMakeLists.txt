# cmake_minimum_required(VERSION 3.5)
# project(my_app)

# set(IS_MYLIB_EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../my_library/build/libmy_library.a)
# if(EXISTS ${IS_MYLIB_EXISTS})
#     message(STATUS ${IS_MYLIB_EXISTS}" exist")

#     # Include directory (assuming my_library.h is in the same folder)
#     set(MY_LIBRARY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../my_library/include)

#     # Set the path to the libmy_library.a file
#     set(LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../my_library/build/libmy_library.a)

#     # Create the executable
#     add_executable(my_app my_app.cpp)

#     # Include the header files from my_library
#     target_include_directories(my_app PRIVATE ${MY_LIBRARY_INCLUDE_DIR})

#     # Link the executable with libmy_library.a
#     target_link_libraries(my_app PRIVATE ${LIBRARY_PATH})
# else()
#     message(FATAL_ERROR ${IS_MYLIB_EXISTS}" did not exist, please build libmy_library.a first on my_library directory")
# endif()


cmake_minimum_required(VERSION 3.5)
project(my_app)

# Enable C++17 standard (change as needed)
set(CMAKE_CXX_STANDARD 17)
# IF DEBUG MEMORY LEAK
set(MEMLEAK TRUE)

set(IS_MYLIB_EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../my_library/build/libmy_library.a)
if(EXISTS ${IS_MYLIB_EXISTS})
    message(STATUS ${IS_MYLIB_EXISTS} " exist")

    # Include directory (assuming my_library.h is in the same folder)
    set(MY_LIBRARY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../my_library/include)

    # Set the path to the libmy_library.a file
    set(LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../my_library/build/libmy_library.a)

    # Create the executable
    add_executable(my_app my_app.cpp)

    # Include the header files from my_library
    target_include_directories(my_app PRIVATE ${MY_LIBRARY_INCLUDE_DIR})

    # Link the executable with libmy_library.a
    target_link_libraries(my_app PRIVATE ${LIBRARY_PATH})

    # Enable AddressSanitizer and debug symbols
    if (MEMLEAK)
        target_compile_options(my_app PRIVATE -fsanitize=address -g)
        target_link_libraries(my_app PRIVATE -fsanitize=address)
    endif()
else()
    message(FATAL_ERROR ${IS_MYLIB_EXISTS} " did not exist, please build libmy_library.a first in the my_library directory")
endif()
