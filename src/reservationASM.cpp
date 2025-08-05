/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file reservationASM.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @manages reservation file operations
 * @version 2
 * @date 2025-08-04
 * 
*/
#include "ReservationASM.h"
#include <iostream>

std::fstream ReservationASM::file;
const std::string ReservationASM::filename = "data/reservations.dat";

void ReservationASM::init(){
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);

     if (!file.is_open()) {
        // File doesn't exist; create it
        file.open(filename, std::ios::binary | std::ios::out);
        file.close();
        file.open(filename, std::ios::binary | std::ios::in | std::ios::out);
    }

}
void ReservationASM::shutdown() {
    if (file.is_open()) {
        file.close();
    }
}
void ReservationASM::addReservation(const Reservation& reservation){
    file.seekp(0, std::ios::end);
    //adding the reservation to the end of the file
    file.write(reinterpret_cast<const char*>(&reservation), sizeof(Reservation));
    file.flush(); // Force write to disk
    file.clear(); // Clear any error flags
}
bool ReservationASM::getNextReservation(Reservation& reservation){
    if (!file.read(reinterpret_cast<char*>(&reservation), sizeof(Reservation))) {
        file.clear(); // Clear EOF flag for subsequent operations
        return false; // Reached end or error
    }
    return true;
}
bool ReservationASM::overwriteReservation(const Reservation& reservation, int index) {
    //finding the position of the index to be removed
    std::streampos pos = static_cast<std::streampos>(index) * sizeof(Reservation);
    //going to position
    file.seekp(pos);
    if (!file) {
        //display error if position is not in system
        std::cerr << "Error: Invalid position.\n";
        return false;
    }
    //overwriting the reservation
    file.write(reinterpret_cast<const char*>(&reservation), sizeof(Reservation));
    file.flush(); // Force write to disk
    file.clear(); // Clear any error flags
    return true;
}
void ReservationASM::seekToBeginning() {
    if (file.is_open()) {
        file.clear(); // Clear any error flags first
        file.seekg(0, std::ios::beg); // Seek to beginning for reading
        file.seekp(0, std::ios::beg); // Also reset write position
    }
}
int ReservationASM::getCurrentID() {
    if (!file.is_open()) {
        return 0;
    }
    file.clear(); // Clear any error flags
    std::streampos currentPos = file.tellg(); // Save current position
    file.seekg(0, std::ios::end); // Seek to end
    std::streampos size = file.tellg(); // Get file size
    file.seekg(currentPos); // Restore position
    return static_cast<int>(size / sizeof(Reservation));
}