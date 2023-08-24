#include <iostream>
#include "sambel.h"
#include <string>

Sambel::Sambel() : jumlah_lombok(0), isPedes(false) {

}

Sambel::Sambel(int jl) : jumlah_lombok(jl) {
    
}

void Sambel::createSambel(int jl, bool ispedes) {
    jumlah_lombok = jl;
    isPedes = ispedes;
}

std::string Sambel::getSambel() {
    std::string beneranPedes = "";
    if (isPedes) {
        beneranPedes = "PEDAS\n";
    } else {
        beneranPedes = "GA PEDAS\n";        
    }
    std::string sentences = std::string("\n\nSambel lombok: ") + std::to_string(jumlah_lombok)  + " dan " + beneranPedes;

    return sentences;
}

void Sambel::sajikanSambel(std::string sen) {
    std::cout << sen << std::endl;
}
