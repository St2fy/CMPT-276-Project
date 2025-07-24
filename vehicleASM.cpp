#include "VehicleASM.h"
#include <iostream>
#include "reservation.h"
std::fstream VehicleASM::file;
const std::string VehicleASM::filename = "vehicles.dat";

void VehicleASM::init(){
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        // Create file if it doesn't exist
        file.open(filename, std::ios::out | std::ios::binary);
        file.close();
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    }
}
void VehicleASM::shutdown() {
    if (file.is_open()) {
        file.close();
    }
}
void VehicleASM::addVehicle(const Vehicle& vehicle) {
    if (!file.is_open()) return;

    file.clear(); // ensure stream is good
    file.seekp(0, std::ios::end);
    file.write(reinterpret_cast<const char*>(&vehicle), sizeof(Vehicle));
}
bool VehicleASM::getNextVehicle(Vehicle& vehicle){
    file.clear();
    return static_cast<bool>(file.read(reinterpret_cast<char*>(&vehicle), sizeof(Vehicle)));

}
void VehicleASM::seekToBeginning() {
    if (file.is_open()) {
        file.clear();
        file.seekg(0);
    }
}

int VehicleASM::getCurrentID() {
    if (!file.is_open()) return -1;

    file.clear();
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();

    return static_cast<int>(size / sizeof(Vehicle));
}