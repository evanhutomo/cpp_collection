#include "lat1.h"
#include <limits.h>
#include <unistd.h>
#include <locale>   // for std::wstring_convert
#include <codecvt>  // for std::codecvt_utf8
#include <array>
#include <cstring>

namespace LATCPP::BASIC1 {
    Latihan1::Latihan1(){}
    Latihan1::~Latihan1(){}   
    
    void Latihan1::t_strcopy(std::array<int,4> arr) {
    int* ptr = arr.data(); // Obtain a pointer to the underlying array using data()
    for (std::size_t i = 0; i < arr.size(); ++i) { // Print the elements of the array using the obtained pointer
        std::cout << *(ptr + i) << " ";
    }
    std::cout << std::endl;
    }

    std::string Latihan1::getExecutablePath()
    {
        char path[PATH_MAX];
        ssize_t length = readlink("/proc/self/exe", path, sizeof(path) - 1);

        if (length != -1)
        {
            path[length] = '\0';
            std::cout << "Executable path: " << path << std::endl;
            return path;
        }
        else
        {
            std::cerr << "Failed to retrieve executable path" << std::endl;
            return "Failed to retrieve executable path";
        }
    }

    void Latihan1::getWindowsPath()
    {
        // example to get path on windows
        std::string helper = "C:\\Users\\evanhutomo\\Documents";

        size_t pos = helper.find_last_of("\\");
        if (pos != std::string::npos)
        {
            std::string directory = helper.substr(0, pos + 1);
            std::cout << "Directory: " << directory << std::endl;
        }
        else
        {
            std::cout << "Backslash not found in the string" << std::endl;
        }
    }

    void Latihan1::exampleStrncpy(std::wstring src) {
        std::wstring source(src);
        std::array<char, 1024> destination;

        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string narrowStr = converter.to_bytes(source);

        strncpy(destination.data(), narrowStr.c_str(), destination.size() - 1);
        destination[destination.size() - 1] = '\0';  // Ensure null-termination

        std::cout << "Source: " << narrowStr << std::endl;
        std::cout << "Destination: " << destination.data() << std::endl;
    }
}