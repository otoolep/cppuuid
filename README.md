cppuuid
=======

C++ UUID support inspired by Python's UUID class (uuid.py).

Quick demo:

#include <iostream>
#include <utility>
#include "uuid.hpp"

int main(void)
{
    std::cout << "Generating uuid..." << std::endl;

    uuid::Uuid u = uuid::uuid1((uint64_t) 0x19432987, (uint16_t) 0x33);
    std::cout << u.hex() << std::endl;
    std::cout <<  std::pair<uint64_t, uint64_t>p = u.integer() << std::endl;

    return 0;
}
