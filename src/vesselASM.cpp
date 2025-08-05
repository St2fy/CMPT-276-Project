/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file vesselASM.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @manages vessel file operations
 * @version 1
 * @date 2025-07-23
 * 
*/
#include "VesselASM.h"
#include <iostream>
std::fstream VesselASM::file;
const std::string VesselASM::filename = "vessels.dat";

void VesselASM::init(){
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        // Create file if it doesn't exist
        file.open(filename, std::ios::out | std::ios::binary);
        file.close();
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    }
}
void VesselASM::shutdown() {
    if (file.is_open()) {
        file.close();
    }
}
void VesselASM::addVessel(const Vessel& vessel) {
    if (!file.is_open()) return;
    // ensure stream is good
    file.clear(); 
    file.seekp(0, std::ios::end);
    file.write(reinterpret_cast<const char*>(&vessel), sizeof(Vessel));
    file.flush(); // Force write to disk
    file.clear(); // Clear any error flags
}
bool VesselASM::getNextVessel(Vessel& vessel) {
    if (!file.read(reinterpret_cast<char*>(&vessel), sizeof(Vessel))) {
        file.clear(); // Clear EOF flag for subsequent operations
        return false; // Reached end or error
    }
    return true;
}
void VesselASM::seekToBeginning() {
    if (file.is_open()) {
        file.clear(); // Clear any error flags first
        file.seekg(0, std::ios::beg); // Seek to beginning for reading
        file.seekp(0, std::ios::beg); // Also reset write position
    }
}

int VesselASM::getCurrentID() {
    if (!file.is_open()) {
        return 0;
    }
    file.clear(); // Clear any error flags
    std::streampos currentPos = file.tellg(); // Save current position
    file.seekg(0, std::ios::end); // Seek to end
    std::streampos size = file.tellg(); // Get file size
    file.seekg(currentPos); // Restore position
    return static_cast<int>(size / sizeof(Vessel));
}