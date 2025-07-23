#include <iostream>
#include <cassert>
#include <cstring>
#include "sailing.h"
#include "sailingASM.h"

using namespace std;

void testSailingDefaultConstructor() {
    std::cout << "Running testSailingDefaultConstructor...\n";
    Sailing sailing;
    assert(strcmp(sailing.getSailingID(), "abc-12-34") == 0);
    assert(strcmp(sailing.getVesselName(), "Queen of Richmond") == 0);
    assert(sailing.getLCLLUsed() == 5.7f);
    assert(sailing.getHCLLUsed() == 77.54f);
    assert(sailing.getPassengers() == 54);
    std::cout << "testSailingDefaultConstructor PASSED\n";
}

void testSailingASMWriteRead() {
    std::cout << "Running testSailingASMWriteRead...\n";
    SailingASM::init();
    SailingASM::seekToBeginning();

    // Write a record
    Sailing sailing;
    SailingASM::addSailing(sailing);

    // Read it back
    Sailing readBack;
    SailingASM::seekToBeginning();
    bool result = SailingASM::getNextSailing(readBack);

    assert(result == true);
    assert(strcmp(readBack.getSailingID(), sailing.getSailingID()) == 0);
    assert(strcmp(readBack.getVesselName(), sailing.getVesselName()) == 0);
    assert(readBack.getLCLLUsed() == sailing.getLCLLUsed());
    assert(readBack.getHCLLUsed() == sailing.getHCLLUsed());
    assert(readBack.getPassengers() == sailing.getPassengers());

    std::cout << "testSailingASMWriteRead PASSED\n";
    SailingASM::shutdown();
}

int main() {
    testSailingDefaultConstructor();
    testSailingASMWriteRead();
    return 0;
}


