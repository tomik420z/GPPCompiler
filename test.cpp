#include <any>
#include <iostream>

int main() {
    std::any x = 10;
    std::cout << std::any_cast<int>(x) << std::endl;
}