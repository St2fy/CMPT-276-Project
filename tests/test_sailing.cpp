#include <iostream>
#include "../include/sailingASM.h"
#include "../include/sailing.h"

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
    
    // Create char arrays for vessel names and sailing IDs
    char vessel1[] = "QueenOfOakBay";
    char sailing1[] = "SAIL001";
    char vessel2[] = "SpiritOfBC";
    char sailing2[] = "SAIL002";
    char vessel3[] = "CoastalRenaissance";
    char sailing3[] = "SAIL003";
    
    Sailing s1(vessel1, sailing1, 12.5f, 7.2f, 25, nullptr);
    Sailing s2(vessel2, sailing2, 20.0f, 14.3f, 40, nullptr);
    Sailing s3(vessel3, sailing3, 18.5f, 8.0f, 30, nullptr);

    SailingASM::addSailing(s1);
    SailingASM::addSailing(s2);
    SailingASM::addSailing(s3);

    // Display all sailings
    printAllSailings();

    // Delete one sailing by ID (delete the second sailing - SAIL002)
    std::cout << "[Deleting Sailing SAIL002]\n";
    SailingASM::seekToBeginning();
    Sailing temp;
    // Skip first sailing
    SailingASM::getNextSailing(temp);
    // Position at second sailing (SAIL002) and delete it
    SailingASM::getNextSailing(temp);
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