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
const std::string VesselASM::filename = "vehicles.dat";

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
}
bool VesselASM::getNextVessel(Vessel& vessel) {
    file.clear();
    if (!file.read(reinterpret_cast<char*>(&vessel), sizeof(Vessel))) {
        // At the end already or error
        return false; 
    }
    return true;
}
void VesselASM::seekToBeginning() {
    if (file.is_open()) {
        file.clear();
        file.seekg(0);
    }
}

int VesselASM::getCurrentID() {
    if (!file.is_open()) {
        return 0;
    }
    // ensure stream is good
    file.clear();
    //finding the index of current file pointer
    std::streampos size = file.tellg();
    return static_cast<int>(size / sizeof(Vessel));
}