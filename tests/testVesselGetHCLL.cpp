/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file testVesselGetHCLL.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief Unit test for getHCLLCap() function
 * @version 1.0
 * @date 2025-07-08
 * 
 * This test validates that vessel.cpp correctly creates a
 * Vessel and getHCLLCap() returns the correct value for 
 * said Vessel object
 */

#include <iostream>
#include <cassert>
#include "vessel.h"

void testGetHCLLCap() {
    std::cout << "Running test: getHCLLCap()\n";

    //Create a vessel with known HCLL value
    char vesselName[] = "Test Vessel";
    float testLCLL = 10.5f;
    float testHCLL = 42.0f;

    Vessel testVessel(vesselName, testLCLL, testHCLL);

    //Check HCLL is correctly returned
    float returnedHCLL = testVessel.getHCLLCap();
    std::cout << "Expected HCLL: " << testHCLL << ", Returned: " << returnedHCLL << "\n";
    assert(returnedHCLL == testHCLL);

    std::cout << "PASS: getHCLLCap() returns correct value.\n";
}

int main() {
    testGetHCLLCap();
    return 0;
}