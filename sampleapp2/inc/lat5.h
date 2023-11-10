#pragma once
/*
for demonstrating Rule of Three
*/

namespace LATCPP::BASIC5 {
    class Latihan5{
        private:
            int id;
            char* name;

        public:
            Latihan5();
            Latihan5(int id, const char* name);
            ~Latihan5();
    }
}