/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file vessel.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @handles testing file operations
 * @version 1
 * @date 2025-07-08
 * 
*/
#include <iostream>
#include <cassert>
#include <cstring>
#include "sailing.h"
#include "sailingASM.h"

void testMultipleSailingRecords() {
    std::cout << "Running multi-record Sailing file test...\n";

    //Init the ASM and start fresh
    SailingASM::init();
    SailingASM::seekToBeginning();

    //Create two Sailing records
    Sailing s1; // default one
    Sailing s2((char*)"Spirit of Vancouver", (char*)"xyz-99-88", 15.5f, 50.0f, 30, nullptr); // custom one

    //Add both to file
    SailingASM::addSailing(s1);
    SailingASM::addSailing(s2);

    //Read both back
    SailingASM::seekToBeginning();
    Sailing r1, r2;
    bool got1 = SailingASM::getNextSailing(r1);
    bool got2 = SailingASM::getNextSailing(r2);
    bool got3 = SailingASM::getNextSailing(r2); // Should be false (EOF)

    //Validate r1
    assert(got1);
    assert(strcmp(r1.getSailingID(), s1.getSailingID()) == 0);
    assert(strcmp(r1.getVesselName(), s1.getVesselName()) == 0);
    assert(r1.getHCLLUsed() == s1.getHCLLUsed());
    assert(r1.getLCLLUsed() == s1.getLCLLUsed());
    assert(r1.getPassengers() == s1.getPassengers());

    //Validate r2
    assert(got2);
    assert(strcmp(r2.getSailingID(), s2.getSailingID()) == 0);
    assert(strcmp(r2.getVesselName(), s2.getVesselName()) == 0);
    assert(r2.getHCLLUsed() == s2.getHCLLUsed());
    assert(r2.getLCLLUsed() == s2.getLCLLUsed());
    assert(r2.getPassengers() == s2.getPassengers());

    //EOF reached
    assert(!got3);

    std::cout << "PASS: All records written, read, and validated.\n";

    SailingASM::shutdown();
}

int main() {
    testMultipleSailingRecords();
    return 0;
}