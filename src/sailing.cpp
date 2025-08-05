/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file sailing.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief manages sailing operations
 * @version 1
 * @date 2025-07-21
 * 
*/

#include "sailing.h"
#include "sailingASM.h"
#include "vessel.h"
#include "vesselASM.h"
#include <cstring>

Sailing::Sailing() {
    vesselName[0] = '\0';
    sailingID[0] = '\0';
    LCLLUsed = 0.0f;
    HCLLUsed = 0.0f;
    passengers = 0;
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
    vessel = nullptr;
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

void Sailing::setHCLLUsed(float hcllUsed) {
    HCLLUsed = hcllUsed;
}

void Sailing::setLCLLUsed(float lcllUsed) {
    LCLLUsed = lcllUsed;
}

void Sailing::setPassengers(int passengerCount) {
    passengers = passengerCount;
}

/**----------------------------------------------
 * creates a sailing, safe against duplicate sailings
 * @param vesselName
 * @param sailingID
 * @param LCLLUsed
 * @param HCLLUsed
 * @param 
 * @return Sailing
 */
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

/**----------------------------------------------
 * deletes a sailing
 * @param sailingID
 * @return bool - true if the deletion is successful false otherwise
 */
bool Sailing::deleteSailing(char* sailingID) {
    SailingASM::seekToBeginning();
    Sailing s;
    while (SailingASM::getNextSailing(s)) {
        if (std::strcmp(s.getSailingID(), sailingID) == 0) {
            SailingASM::deleteSailing();
            return true;
        }
    }
    return false;
}

/**----------------------------------------------
 * initiates a search for a sailing
 * @param sailingID
 * @return Sailing
 */
Sailing Sailing::querySailing(char* sailingID) {
    SailingASM::seekToBeginning();
    Sailing s;
    while (SailingASM::getNextSailing(s)) {
        if (std::strcmp(s.getSailingID(), sailingID) == 0) {
            return s;
        }
    }
    return Sailing(); // empty sailing
}

/**----------------------------------------------
 * updates an existing sailing
 * @param sailingID
 * @param sailing - the updated sailing object
 * @return bool - true if the update is successful false otherwise
 */
bool Sailing::updateSailing(char* sailingID, const Sailing& sailing) {
    SailingASM::seekToBeginning();
    Sailing s;
    int index = 0;
    while (SailingASM::getNextSailing(s)) {
        if (std::strcmp(s.getSailingID(), sailingID) == 0) {
            // Found the sailing to update
            return SailingASM::overwriteSailing(sailing, index);
        }
        index++;
    }
    return false; // Sailing not found
}

/**----------------------------------------------
 * startup function
 */
void Sailing::init() {
    SailingASM::init();
}

/**----------------------------------------------
 * shutdown function
 */
void Sailing::shutdown() {
    SailingASM::shutdown();
}