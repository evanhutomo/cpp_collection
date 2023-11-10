/*
    for demonstrating Rule of Three
    desc: 
    manually manage a dynamically allocated resources
*/
#include "lat5.h"
#include <iostream>

namespace LATCPP::BASIC6 {
    Latihan6::Latihan6(){
        this->id = 0;
        this->name = nullptr;
    }

    Latihan6::Latihan6(int id, const char* name){
        this->id = id;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    Latihan6::~Latihan6(){
        delete[] this->name;
    }
}
