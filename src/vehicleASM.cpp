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
}
bool VehicleASM::getNextVehicle(Vehicle& vehicle){
    file.clear();
    if(!file.read(reinterpret_cast<char*>(&vehicle), sizeof(Vehicle))){
        return false;
    }
    return true;
}
void VehicleASM::seekToBeginning() {
    if (file.is_open()) {
        file.clear();
        //go back to the start with 0  offset
        file.seekg(0);
    }
}

int VehicleASM::getCurrentID() {
    if (!file.is_open()) return -1;

    file.clear();
    //finding the index of current file pointer
    std::streampos size = file.tellg();

    return static_cast<int>(size / sizeof(Vehicle));
}