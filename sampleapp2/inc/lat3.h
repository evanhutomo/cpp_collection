#pragma once

namespace LATCPP::BASIC3 {
    class Latihan3 {
        private:
            int m_a;
            int m_b;
        public:
            Latihan3();
            Latihan3(int a, int b): m_a(a), m_b(b){} // If you do constructor like this, you musnt define again on .cpp 
            ~Latihan3();
            void testLat3();
    };
}