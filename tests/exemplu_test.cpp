#include "EfectEcou.h"
#include <cassert>
#include <iostream>

int main() {
    EfectEcou ecou("EcouTest", true, 5, 0.4f);
    assert(ecou.getNume() == "EcouTest");
    assert(ecou.esteActiv() == true);

    std::cout << "Testele unitare au trecut cu succes!\n";
    return 0;
}
