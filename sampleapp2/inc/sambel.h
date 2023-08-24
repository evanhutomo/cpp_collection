#pragma once

class Sambel {
    private:
        int jumlah_lombok;
        bool isPedes;

    public:
        Sambel();
        Sambel(int jumlah_lombok);
        ~Sambel() = default;
        void createSambel(int jumlah_lombok, bool isPedes);
        std::string getSambel();
        void sajikanSambel(std::string sen);
};