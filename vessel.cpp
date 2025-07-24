#include "vessel.h"

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