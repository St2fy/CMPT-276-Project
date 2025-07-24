#include <iostream>
#include <cassert>
#include <cstring>
#include "sailing.h"
#include "sailingASM.h"


void testSailingASM(){
    std::cout << "Run testsailingASM \n";

    //Initialize SailingASM
    SailingASM::init();

    //Seek to beginning of file
    SailingASM::seekToBeginning();

    Sailing sailing;
    SailingASM::addSailing(sailing);

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
        std::cout << " Failed to read record back.\n";
    }



    SailingASM::shutdown();
}

int main(){
    testSailingASM();
    return 0;
}