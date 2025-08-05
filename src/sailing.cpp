/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file sailing.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief manages sailing operations
 * @version 2
 * @date 2025-08-04
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
    vessel = nullptr;
}

Sailing::Sailing(const char* vn, const char* sid, float lcllu, float hcllu, Vessel* v) {
    strcpy(vesselName, vn);
    strcpy(sailingID, sid);
    LCLLUsed = lcllu;
    HCLLUsed = hcllu;
    vessel = v;
}

Sailing::~Sailing() {
    vessel = nullptr;
}

const char* Sailing::getSailingID() const {
    return sailingID;
}

const char* Sailing::getVesselName() const {
    return vesselName;
}

float Sailing::getHCLLUsed() const {
    return HCLLUsed;
}

float Sailing::getLCLLUsed() const {
    return LCLLUsed;
}

void Sailing::setHCLLUsed(float hcllUsed) {
    HCLLUsed = hcllUsed;
}

void Sailing::setLCLLUsed(float lcllUsed) {
    LCLLUsed = lcllUsed;
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
Sailing* Sailing::createSailing(const char* vesselName, const char* sailingID, float LCLLUsed, float HCLLUsed, Vessel* vessel) {
    SailingASM::seekToBeginning();
    Sailing s;
    while (SailingASM::getNextSailing(s)) {
        if (strcmp(s.getSailingID(), sailingID) == 0) {
            // Duplicate sailing ID found
            return nullptr; // Return a null pointer
        }
    }
    SailingASM::addSailing(Sailing(vesselName, sailingID, LCLLUsed, HCLLUsed, vessel));
    return new Sailing(vesselName, sailingID, LCLLUsed, HCLLUsed, vessel);
}

/**----------------------------------------------
 * deletes a sailing
 * @param sailingID
 * @return bool - true if the deletion is successful false otherwise
 */
bool Sailing::deleteSailing(const char* sailingID) {
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
Sailing Sailing::querySailing(const char* sailingID) {
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
bool Sailing::updateSailing(const char* sailingID, const Sailing& sailing) {
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