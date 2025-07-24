#include "sailing.h"
#include "sailingASM.cpp"
#include <cstring>
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
Sailing* Sailing::createSailing(char* vesselName, char* sailingID, float LCLLUsed, float HCLLUsed, int passengers, Vessel* vessel) {
    SailingASM::seekToBeginning();
    Sailing s;
    while (SailingASM::getNextSailing(s)) {
        if (strcmp(s.getSailingID(), sailingID) == 0) {
            // Duplicate sailing ID found
            return nullptr; // Return a null pointer
        }
    }
    SailingASM::addSailing(Sailing(vesselName, sailingID, LCLLUsed, HCLLUsed, passengers, vessel));
    return new Sailing(vesselName, sailingID, LCLLUsed, HCLLUsed, passengers, vessel);
}
bool Sailing::deleteSailing(char* sailingID) {
    SailingASM::seekToBeginning();
    Sailing s;
    while (SailingASM::getNextSailing(s)) {
        if (strcmp(s.getSailingID(), sailingID) == 0) {
            SailingASM::deleteSailing();
            return true; // Deletion successful
        }
    }
    return false; // Sailing ID not found
}
Sailing* Sailing::querySailing(char* sailingID) {
    SailingASM::seekToBeginning();
    Sailing s;
    while (SailingASM::getNextSailing(s)) {
        if (strcmp(s.getSailingID(), sailingID) == 0) {
            return new Sailing(s); // Return a copy of the found sailing
        }
    }
    return nullptr; // Return a null pointer if not found
}
std::string Sailing::to_string() {
    std::string result = "Sailing ID: " + std::string(sailingID) + "\n" +
                         "Vessel Name: " + std::string(vesselName) + "\n" +
                         "LCLL Used: " + std::to_string(LCLLUsed) + "\n" +
                         "HCLL Used: " + std::to_string(HCLLUsed) + "\n" +
                         "Passengers: " + std::to_string(passengers) + "\n";
    return result;
}