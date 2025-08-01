/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file vessel.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handles vessel operations
 * @version 1
 * @date 2025-07-23
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

Vessel::Vessel(char* n, float lcll, float hcll) {
    strcpy(name, n);
    LCLLCapacity = lcll;
    HCLLCapacity = hcll;
    passengerCapacity = 0;
}

Vessel::~Vessel() {
    // No dynamic memory to clean up
}

char* Vessel::getName() {
    return name;
}

float Vessel::getLCLLCap() {
    return LCLLCapacity;
}

float Vessel::getHCLLCap() {
    return HCLLCapacity;
}

int Vessel::getPassengerCap() {
    return passengerCapacity;
}

/**----------------------------------------------
 * creates a vessel, safe against duplicate vessels
 * @param name
 * @param LCLL
 * @param HCLL
 * @return Vessel
 */
Vessel* Vessel::createVessel(char* name, float LCLL, float HCLL) {
    VesselASM::seekToBeginning();
    Vessel v(name, LCLL, HCLL);
    while (VesselASM::getNextVessel(v)) {
        if (strcmp(v.getName(), name) == 0) {
            // Duplicate vessel found
            return nullptr;
        }
    }
    VesselASM::addVessel(v);
    return new Vessel(name, LCLL, HCLL);
}

/**----------------------------------------------
 * initiates a search for a vessel
 * @param name
 * @return Vessel
 */
Vessel Vessel::queryVessel(char* name) {
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
