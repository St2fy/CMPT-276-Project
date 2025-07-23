#include "sailing.h"
#include <cstring>
// default constructor for testing purposes
Sailing::Sailing() {
    strcpy(vesselName,"Queen of Richmond");
    strcpy(sailingID, "abc-12-34");
    LCLLUsed = 5.7;
    HCLLUsed = 77.54;
    passengers = 54;
    vessel = nullptr;
}
Sailing::~Sailing() {
    return;
}
char* Sailing::getSailingID() {
    return sailingID;
}
char* Sailing::getVesselName() {
    return vesselName;
}
float Sailing::getHCLLUsed() {
    return HCLLUsed;
}
float Sailing::getLCLLUsed() {
    return LCLLUsed;
}
int Sailing::getPassengers() {
    return passengers;
}