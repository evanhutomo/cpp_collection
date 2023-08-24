#pragma once
#include <array>
#include <iostream>

namespace LATCPP::BASIC1 {
    class Latihan1 {
        private:
            std::array<int, 4> m_arr;
        public:
            Latihan1();
            ~Latihan1();
            void t_strcopy(std::array<int,4> a);
            std::string getExecutablePath();
            void getWindowsPath();
            void exampleStrncpy(std::wstring src);
    };

}