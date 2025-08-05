/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file testFileOps.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief Unit test for low-level file write and read (SailingASM)
 * @version 2
 * @date 2025-08-05
 * 
 * This test validates that SailingASM correctly writes and reads
 * multiple sailing records to and from a binary file.
 */

#include <iostream>
#include <cassert>
#include <cstring>
#include "sailing.h"
#include "sailingASM.h"

void testMultipleSailingRecords() {
    std::cout << "STARTING UNIT TEST: testFileOps.cpp \n\n";

    std::cout << "[1]Initializing SailingASM system\n";
    SailingASM::init();

    std::cout << "[2] Seeking to beginning of file\n";
    SailingASM::seekToBeginning();

    // Create and log two Sailing records
    std::cout << "[3] Creating two Sailing records\n";
    Sailing s1; 
    Sailing s2((char*)"Spirit of Vancouver", (char*)"xyz-99-88", 15.5f, 50.0f, 30, nullptr);

    std::cout << "    -> Sailing #1: "
              << s1.getSailingID() << ", " << s1.getVesselName() << "\n";
    std::cout << "    -> Sailing #2: "
              << s2.getSailingID() << ", " << s2.getVesselName() << "\n";

    //Write records to file
    std::cout << "[4]Writing both Sailing records to file\n";
    SailingASM::addSailing(s1);
    SailingASM::addSailing(s2);

    std::cout <<"[5] Rewinding file to beginning\n";
    SailingASM::seekToBeginning();

    // Read back records
    Sailing r1, r2;
    std::cout << "[6]Reading back first Sailing record\n";
    bool got1 = SailingASM::getNextSailing(r1);
    assert(got1);

    std::cout << "   -> Read Sailing #1: "
              << r1.getSailingID() << ", " << r1.getVesselName() << "\n";

    std::cout << "[7] Verifying Sailing #1 fields\n";
    assert(strcmp(r1.getSailingID(), s1.getSailingID()) == 0);
    assert(strcmp(r1.getVesselName(), s1.getVesselName()) == 0);
    assert(r1.getHCLLUsed() == s1.getHCLLUsed());
    assert(r1.getLCLLUsed() == s1.getLCLLUsed());
    assert(r1.getPassengers() == s1.getPassengers());

    std::cout << "[8] Reading back second Sailing record\n";
    bool got2 = SailingASM::getNextSailing(r2);
    assert(got2);

    std::cout << "    -> Read Sailing #2: "
              << r2.getSailingID() << ", " << r2.getVesselName() << "\n";

    std::cout << "[9] Verifying Sailing #2 fields\n";
    assert(strcmp(r2.getSailingID(), s2.getSailingID()) == 0);
    assert(strcmp(r2.getVesselName(), s2.getVesselName()) == 0);
    assert(r2.getHCLLUsed() == s2.getHCLLUsed());
    assert(r2.getLCLLUsed() == s2.getLCLLUsed());
    assert(r2.getPassengers() == s2.getPassengers());

    std::cout << "[10] Attempting third read to check EOF\n";
    bool got3 = SailingASM::getNextSailing(r2);
    if (!got3) {
        std::cout << "    -> Reached end of file as expected.\n";
    } else {
        std::cerr << "    !! ERROR: Unexpected record found after expected EOF.\n";
        assert(false);
    }

    std::cout << "\nPASS: All Sailing records written, read, and validated. \n";

    std::cout << "[11]Shutting down SailingASM system\n";
    SailingASM::shutdown();

    std::cout << "\nEND OF UNIT TEST \n";
}

int main() {
    testMultipleSailingRecords();
    return 0;
}
