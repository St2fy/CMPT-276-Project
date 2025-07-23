#include <iostream>
#include "sailingASM.h"
#include "sailing.h"

void printAllSailings() {
    SailingASM::seekToBeginning();
    Sailing s;
    std::cout << "----- Current Sailings in File -----\n";
    while (SailingASM::getNextSailing(s)) {
        std::cout << "Vessel: " << s.getVesselName()
                  << ", ID: " << s.getSailingID()
                  << ", LCLL: " << s.getLCLLUsed()
                  << ", HCLL: " << s.getHCLLUsed()
                  << ", Passengers: " << s.getPassengers()
                  << "\n";
    }
    std::cout << "------------------------------------\n";
}

int main() {
    // Start system
    SailingASM::init();

    // Add sample sailings
    std::cout << "[Adding Test Sailings...]\n";
    
    Sailing s1("QueenOfOakBay", "SAIL001", 12.5f, 7.2f);
    Sailing s2("SpiritOfBC", "SAIL002", 20.0f, 14.3f);
    Sailing s3("CoastalRenaissance", "SAIL003", 18.5f, 8.0f);

    SailingASM::addSailing(s1);
    SailingASM::addSailing(s2);
    SailingASM::addSailing(s3);

    // Display all sailings
    printAllSailings();

    // Delete one sailing by ID
    std::cout << "[Deleting Sailing ]\n";
    SailingASM::deleteSailing();
    // Show sailings after deletion
    printAllSailings();

    // Display total records left
    int count = SailingASM::getCurrentID();
    std::cout << "Total Records After Deletion: " << count << "\n";

    // Clean shutdown
    SailingASM::shutdown();
    return 0;
}