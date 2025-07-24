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
Sailing::Sailing(char* vn, char* sid, float lcllu, float hcllu, int p, Vessel* v) {
    strcpy(vesselName, vn);
    strcpy(sailingID, sid);
    LCLLUsed = lcllu;
    HCLLUsed = hcllu;
    passengers = p;
    vessel = v;
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