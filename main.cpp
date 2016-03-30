////////////////////////////////////////////////////////////////////////////////
//
// main.cpp
//
// Demo program showing how to use Uuid class.

#include <iostream>
#include "uuid.hpp"

int main(void)
{
    std::cout << "Generating UUID...." << std::endl;

    uuid::Uuid u = uuid::uuid1((uint64_t) 0x19432987, (uint16_t) 0x33);
    std::pair<uint64_t, uint64_t>p = u.integer();
    std::cout << p.first << p.second << std::endl;
    return 0;
}
