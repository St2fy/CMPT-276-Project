/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file vehicleASM.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @manages vehicle file operations
 * @version 1
 * @date 2025-07-23
 * 
*/
#include "vehicleASM.h"
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
    // ensure stream is good
    file.clear(); 
    file.seekp(0, std::ios::end);
    //reinterpret cast to create new vehicle
    file.write(reinterpret_cast<const char*>(&vehicle), sizeof(Vehicle));
    file.flush(); // Force write to disk
    file.clear(); // Clear any error flags
}
bool VehicleASM::getNextVehicle(Vehicle& vehicle){
    if(!file.read(reinterpret_cast<char*>(&vehicle), sizeof(Vehicle))){
        file.clear(); // Clear EOF flag for subsequent operations
        return false;
    }
    return true;
}
void VehicleASM::seekToBeginning() {
    if (file.is_open()) {
        file.clear(); // Clear any error flags first
        file.seekg(0, std::ios::beg); // Seek to beginning for reading
        file.seekp(0, std::ios::beg); // Also reset write position
    }
}

int VehicleASM::getCurrentID() {
    if (!file.is_open()) return 0;

    file.clear(); // Clear any error flags
    std::streampos currentPos = file.tellg(); // Save current position
    file.seekg(0, std::ios::end); // Seek to end
    std::streampos size = file.tellg(); // Get file size
    file.seekg(currentPos); // Restore position
    return static_cast<int>(size / sizeof(Vehicle));
}