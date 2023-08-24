#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "../my_library/include/my_library.h"

class SomeClass {
public:
    SomeClass(const std::string& description) : description_(description) {}
    void printDescription() const {
        std::cout << "Description: " << description_ << std::endl;
    }

private:
    std::string description_;
};

int main() {
    std::string t_m = "1,W,121,2,20,1,0000000000,0,1,0,dddddd.txt,";
    std::stringstream tmp{ t_m };
    std::string tmp01{};
    std::vector<std::string> to{};
    while (std::getline(tmp, tmp01, ',')) {
        to.push_back(tmp01);
    }

    for (const auto& item : to) {
        std::cout << "Element: " << item << std::endl;
    }

    // Declare and initialize an unordered_map with string keys and SomeClass values
    std::unordered_map<std::string, std::unique_ptr<SomeClass>> data_map;

    // Initialize with empty unique_ptrs
    data_map["item1"] = nullptr;
    data_map["item2"] = nullptr;
    data_map["item3"] = nullptr;
    data_map["item4"] = nullptr;

    // Access and use elements (since they're nullptr, make sure to check before using)
    auto it = data_map.find("item1");
    if (it != data_map.end()) {
        if (it->second) {
            std::cout << "Found item1: ";
            it->second->printDescription();
        } else {
            std::cout << "item1 is empty." << std::endl;
        }
    }

    // Iterate through the elements
    for (const auto& pair : data_map) {
        std::cout << pair.first << ": ";
        if (pair.second) {
            pair.second->printDescription();
        } else {
            std::cout << "Empty" << std::endl;
        }
    }

    // Erase an element by key
    data_map.erase("item2");

    // Check if an element exists after erasing
    if (data_map.find("item2") == data_map.end()) {
        std::cout << "Item2 was erased." << std::endl;
    }
    
    // If you want to test memory leak
    // leak();
    int result_add = add(20, 10);
    int result_subtract = subtract(20, 10);
    std::cout << "Result of add: " << result_add << std::endl;
    std::cout << "Result of subtract: " << result_subtract << std::endl;
    
    return 0;
}
