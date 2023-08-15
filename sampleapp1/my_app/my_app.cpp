#include <iostream>
#include "../my_library/include/my_library.h"
// #include "adapter.h"

int main() {
    int result_add = add(20, 10);
    int result_subtract = subtract(20, 10);
    
    // If you want to test memory leak
    // leak();

    std::cout << "Result of add: " << result_add << std::endl;
    std::cout << "Result of subtract: " << result_subtract << std::endl;
    
    return 0;
}
