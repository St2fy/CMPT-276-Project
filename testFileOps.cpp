// testFileOps.cpp
// Version History:
// v1.0 – Unit test for SailingASM file writing
//        Tests addSailing() by writing and reading back a Sailing record

#include <iostream>
#include <cassert>
#include <cstring>
#include "sailing.h"
#include "sailingASM.h"

void testSailingASM() {
    std::cout << "Testing file write and read for Sailing records \n";

    //Initialize SailingASM
    SailingASM::init();
    SailingASM::seekToBeginning();

    //Write a default sailing record
    Sailing sailing;
    SailingASM::addSailing(sailing);

    //Read it back
    SailingASM::seekToBeginning();
    Sailing readBack;
    bool result = SailingASM::getNextSailing(readBack);

    if (result) {
        std::cout << "Read back Sailing record:\n";
        std::cout << "ID: " << readBack.getSailingID() << "\n";
        std::cout << "Vessel: " << readBack.getVesselName() << "\n";
        std::cout << "HCLL: " << readBack.getHCLLUsed() << "\n";
        std::cout << "LCLL: " << readBack.getLCLLUsed() << "\n";
        std::cout << "Passengers: " << readBack.getPassengers() << "\n";
    } else {
        std::cerr << "Failed to read record back.\n";
    }

    // \Validate the read record matches the written one
    assert(strcmp(readBack.getSailingID(), sailing.getSailingID()) == 0);  
    assert(strcmp(readBack.getVesselName(), sailing.getVesselName()) == 0);
    assert(readBack.getHCLLUsed() == sailing.getHCLLUsed());
    assert(readBack.getLCLLUsed() == sailing.getLCLLUsed());
    assert(readBack.getPassengers() == sailing.getPassengers());

    std::cout << "All assertions passed.\n";

    SailingASM::shutdown();
}

int main() {
    testSailingASM();
    return 0;
}