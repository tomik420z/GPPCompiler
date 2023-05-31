#include <any>
#include <iostream>
#include "variable.h"
#include "hash_set.h"
#include <vector>
int main() {
    std::vector<variable> vec;
    hash_set x;
    x.add_the_first_missing();
    x.add_the_first_missing();
    x.add_the_first_missing();
    int z = 10;
    std::string name = "aasaa";
    for(size_t i = 0; i < 10; ++i) {
        if (i % 2) {
            variable p1(name, x);
            vec.push_back(p1);
        } else {
            variable p2(name, z);
            vec.push_back(p2);
        }
    }

    for(auto & var : vec) {
        std::cout << var << std::endl;
    }
         
}