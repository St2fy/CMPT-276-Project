/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file vessel.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handles vessel operations
 * @version 2
 * @date 2025-08-04
 * 
*/

#include "vessel.h"
#include "vesselASM.h"
#include <cstring>

Vessel::Vessel() {
    name[0] = '\0'; // Initialize name to an empty string
    LCLLCapacity = 0.0f;
    HCLLCapacity = 0.0f;
    passengerCapacity = 0;
}

Vessel::Vessel(const char* n, float lcll, float hcll) {
    strcpy(name, n);
    LCLLCapacity = lcll;
    HCLLCapacity = hcll;
    passengerCapacity = 0;
}

Vessel::~Vessel() {
    // No dynamic memory to clean up
}

const char* Vessel::getName() const {
    return name;
}

float Vessel::getLCLLCap() const {
    return LCLLCapacity;
}

float Vessel::getHCLLCap() const {
    return HCLLCapacity;
}

int Vessel::getPassengerCap() const {
    return passengerCapacity;
}

/**----------------------------------------------
 * creates a vessel, safe against duplicate vessels
 * @param name
 * @param LCLL
 * @param HCLL
 * @return Vessel
 */
Vessel* Vessel::createVessel(const char* name, float LCLL, float HCLL) {
    VesselASM::seekToBeginning();
    
    // Check for duplicates using a separate vessel object
    Vessel existingVessel;
    while (VesselASM::getNextVessel(existingVessel)) {
        if (strcmp(existingVessel.getName(), name) == 0) {
            // Duplicate vessel found
            return nullptr;
        }
    }
    
    // Create the new vessel with the correct values
    Vessel newVessel(name, LCLL, HCLL);
    VesselASM::addVessel(newVessel);
    return new Vessel(name, LCLL, HCLL);
}

/**----------------------------------------------
 * initiates a search for a vessel
 * @param name
 * @return Vessel
 */
Vessel Vessel::queryVessel(const char* name) {
    VesselASM::seekToBeginning();
    Vessel v;
    while (VesselASM::getNextVessel(v)) {
        if (strcmp(v.getName(), name) == 0) {
            return v;
        }
    }
    return Vessel(); // Not found
}

/**----------------------------------------------
 * startup function
 */
void Vessel::init() {
    VesselASM::init();
}

/**----------------------------------------------
 * shutdown function
 */
void Vessel::shutdown() {
    VesselASM::shutdown();
}
