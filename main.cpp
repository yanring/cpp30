#include <iostream>
#include "auto_pointer.hpp"
#include "move.hpp"
#include "container.hpp"
#include "container_with_function.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
//    auto_pointer();
//    move();
//    container();
    container_with_function();
    return 0;
}
