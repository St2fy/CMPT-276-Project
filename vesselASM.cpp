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

    file.clear(); // ensure stream is good
    file.seekp(0, std::ios::end);
    file.write(reinterpret_cast<const char*>(&vessel), sizeof(Vessel));
}
bool VesselASM::getNextVessel(Vessel& vessel) {
    if (!file.is_open()) return false;
    
    return static_cast<bool>( file.read(reinterpret_cast<char*>(&vessel), sizeof(Vessel)));
}
void VesselASM::seekToBeginning() {
    if (file.is_open()) {
        file.clear();
        file.seekg(0);
    }
}

int VesselASM::getCurrentID() {
    if (!file.is_open()) return -1;

    file.clear();
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();

    return static_cast<int>(size / sizeof(Vessel));
}