#include "vessel.h"
#include "vesselASM.cpp"
#include <cstring>

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
Vessel::Vessel() {
    strcpy(name, "Default Vessel");
    LCLLCapacity = 0.0f;
    HCLLCapacity = 0.0f;
    passengerCapacity = 0;
}
Vessel::Vessel(char* name, float LCLL, float HCLL) {
    strcpy(this->name, name);
    this->LCLLCapacity = LCLL;
    this->HCLLCapacity = HCLL;
    this->passengerCapacity = 0;
}
Vessel* createVessel(char* name, float LCLL, float HCLL) {
    VesselASM::seekToBeginning();
    Vessel v(name, LCLL, HCLL);
    while (VesselASM::getNextVessel(v)) {
        if (strcmp(v.getName(), name) == 0) {
            // Duplicate vessel found
            return nullptr; // Return a null pointer
        }
    }
    VesselASM::addVessel(v);
    return new Vessel(name, LCLL, HCLL);
}
Vessel* Vessel::queryVessel(char* name) {
    VesselASM::seekToBeginning();
    Vessel v;
    while (VesselASM::getNextVessel(v)) {
        if (strcmp(v.getName(), name) == 0) {
            return new Vessel(v); // Return a copy of the found vessel
        }
    }
    return nullptr; // Return a null pointer if not found
}
