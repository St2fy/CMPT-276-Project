/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file test_sailing_functionality.cpp
 * @author Test File
 * @brief Comprehensive test for Sailing class functionality
 * @version 1
 * @date 2025-08-04
 * 
*/

#include <iostream>
#include <cstring>
#include <cassert>
#include "sailing.h"
#include "vessel.h"

void testSailingCreation() {
    std::cout << "\n=== Testing Sailing Creation ===\n";
    
    // Create a test vessel
    Vessel* testVessel = new Vessel();
    
    // Test successful sailing creation
    char vesselName[] = "TestVessel";
    char sailingID[] = "SAIL001";
    float LCLLUsed = 15.5f;
    float HCLLUsed = 8.2f;
    int passengers = 50;
    
    Sailing* newSailing = Sailing::createSailing(vesselName, sailingID, LCLLUsed, HCLLUsed, passengers, testVessel);
    
    if (newSailing != nullptr) {
        std::cout << "Sailing created successfully\n";
        std::cout << "  Vessel Name: " << newSailing->getVesselName() << "\n";
        std::cout << "  Sailing ID: " << newSailing->getSailingID() << "\n";
        std::cout << "  LCLL Used: " << newSailing->getLCLLUsed() << "\n";
        std::cout << "  HCLL Used: " << newSailing->getHCLLUsed() << "\n";
        std::cout << "  Passengers: " << newSailing->getPassengers() << "\n";
        
        // Test duplicate prevention
        std::cout << "\n--- Testing Duplicate Prevention ---\n";
        Sailing* duplicateSailing = Sailing::createSailing(vesselName, sailingID, 20.0f, 10.0f, 75, testVessel);
        if (duplicateSailing == nullptr) {
            std::cout << "Duplicate sailing creation prevented\n";
        } else {
            std::cout << "Duplicate sailing was created (should not happen)\n";
            delete duplicateSailing;
        }
        
        delete newSailing;
    } else {
        std::cout << "Failed to create sailing\n";
    }
    
    delete testVessel;
}

void testSailingQuery() {
    std::cout << "\n=== Testing Sailing Query ===\n";
    
    // Create a test vessel
    Vessel* testVessel = new Vessel();
    
    // Create a sailing first
    char vesselName[] = "QueryVessel";
    char sailingID[] = "SAIL002";
    float LCLLUsed = 25.0f;
    float HCLLUsed = 12.5f;
    int passengers = 100;
    
    Sailing* createdSailing = Sailing::createSailing(vesselName, sailingID, LCLLUsed, HCLLUsed, passengers, testVessel);
    
    if (createdSailing != nullptr) {
        std::cout << "Test sailing created for query test\n";
        
        // Test querying existing sailing
        Sailing queriedSailing = Sailing::querySailing(sailingID);
        if (strlen(queriedSailing.getSailingID()) > 0) {
            std::cout << "Sailing found by query\n";
            std::cout << "  Found Vessel: " << queriedSailing.getVesselName() << "\n";
            std::cout << "  Found ID: " << queriedSailing.getSailingID() << "\n";
            std::cout << "  Found LCLL: " << queriedSailing.getLCLLUsed() << "\n";
            std::cout << "  Found HCLL: " << queriedSailing.getHCLLUsed() << "\n";
            std::cout << "  Found Passengers: " << queriedSailing.getPassengers() << "\n";
        } else {
            std::cout << "Sailing not found by query\n";
        }
        
        // Test querying non-existent sailing
        char nonExistentID[] = "NONEXIST";
        Sailing notFoundSailing = Sailing::querySailing(nonExistentID);
        if (strlen(notFoundSailing.getSailingID()) == 0) {
            std::cout << "Non-existent sailing correctly returned empty result\n";
        } else {
            std::cout << "Non-existent sailing query returned unexpected result\n";
        }
        
        delete createdSailing;
    } else {
        std::cout << "Failed to create test sailing for query\n";
    }
    
    delete testVessel;
}

void testSailingDeletion() {
    std::cout << "\n=== Testing Sailing Deletion ===\n";
    
    // Create a test vessel
    Vessel* testVessel = new Vessel();
    
    // Create a sailing to delete
    char vesselName[] = "DeleteVessel";
    char sailingID[] = "SAIL003";
    float LCLLUsed = 30.0f;
    float HCLLUsed = 15.0f;
    int passengers = 80;
    
    Sailing* createdSailing = Sailing::createSailing(vesselName, sailingID, LCLLUsed, HCLLUsed, passengers, testVessel);
    
    if (createdSailing != nullptr) {
        std::cout << "Test sailing created for deletion test\n";
        
        // Verify sailing exists before deletion
        Sailing beforeDelete = Sailing::querySailing(sailingID);
        if (strlen(beforeDelete.getSailingID()) > 0) {
            std::cout << "Sailing confirmed to exist before deletion\n";
            
            // Delete the sailing
            bool deleteResult = Sailing::deleteSailing(sailingID);
            if (deleteResult) {
                std::cout << "Sailing deletion returned true\n";
                
                // Verify sailing no longer exists
                Sailing afterDelete = Sailing::querySailing(sailingID);
                if (strlen(afterDelete.getSailingID()) == 0) {
                    std::cout << "Sailing successfully deleted (not found in query)\n";
                } else {
                    std::cout << "Sailing still exists after deletion\n";
                }
            } else {
                std::cout << "Sailing deletion returned false\n";
            }
        } else {
            std::cout << "Sailing not found before deletion attempt\n";
        }
        
        delete createdSailing;
    } else {
        std::cout << "Failed to create test sailing for deletion\n";
    }
    
    // Test deleting non-existent sailing
    char nonExistentID[] = "NONEXIST";
    bool deleteNonExistent = Sailing::deleteSailing(nonExistentID);
    if (!deleteNonExistent) {
        std::cout << "Deleting non-existent sailing correctly returned false\n";
    } else {
        std::cout << "Deleting non-existent sailing returned true (unexpected)\n";
    }
    
    delete testVessel;
}

void testSailingGetters() {
    std::cout << "\n=== Testing Sailing Getters ===\n";
    
    // Create a test vessel
    Vessel* testVessel = new Vessel();
    
    // Create a sailing with known values
    char vesselName[] = "GetterVessel";
    char sailingID[] = "SAIL004";
    float LCLLUsed = 35.7f;
    float HCLLUsed = 18.3f;
    int passengers = 95;
    
    Sailing testSailing(vesselName, sailingID, LCLLUsed, HCLLUsed, passengers, testVessel);
    
    // Test all getters
    if (strcmp(testSailing.getVesselName(), vesselName) == 0) {
        std::cout << "getVesselName() returns correct value: " << testSailing.getVesselName() << "\n";
    } else {
        std::cout << "getVesselName() returns incorrect value\n";
    }
    
    if (strcmp(testSailing.getSailingID(), sailingID) == 0) {
        std::cout << "getSailingID() returns correct value: " << testSailing.getSailingID() << "\n";
    } else {
        std::cout << "getSailingID() returns incorrect value\n";
    }
    
    if (testSailing.getLCLLUsed() == LCLLUsed) {
        std::cout << "getLCLLUsed() returns correct value: " << testSailing.getLCLLUsed() << "\n";
    } else {
        std::cout << "getLCLLUsed() returns incorrect value\n";
    }
    
    if (testSailing.getHCLLUsed() == HCLLUsed) {
        std::cout << "getHCLLUsed() returns correct value: " << testSailing.getHCLLUsed() << "\n";
    } else {
        std::cout << "getHCLLUsed() returns incorrect value\n";
    }
    
    if (testSailing.getPassengers() == passengers) {
        std::cout << "getPassengers() returns correct value: " << testSailing.getPassengers() << "\n";
    } else {
        std::cout << "getPassengers() returns incorrect value\n";
    }
    
    delete testVessel;
}

int main() {
    std::cout << "=== Sailing Functionality Test Suite ===\n";
    std::cout << "Testing high-level Sailing class methods...\n";
    
    // Initialize the sailing system
    Sailing::init();
    
    try {
        // Run all tests
        testSailingGetters();
        testSailingCreation();
        testSailingQuery();
        testSailingDeletion();
        
        std::cout << "\n=== Test Suite Complete ===\n";
        std::cout << "All tests have been executed.\n";
        std::cout << "Check the output above for any failed tests (marked with ✗).\n";
        
    } catch (const std::exception& e) {
        std::cout << "Exception caught during testing: " << e.what() << "\n";
    }
    
    // Shutdown the sailing system
    Sailing::shutdown();
    
    return 0;
}
