/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file reservationASM.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @manages reservation file operations
 * @version 1
 * @date 2025-07-23
 * 
*/
#include "ReservationASM.h"
#include <iostream>

std::fstream ReservationASM::file;
const std::string ReservationASM::filename = "reservations.dat";

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
}
bool ReservationASM::getNextReservation(Reservation& reservation){
    file.clear();
    if (!file.read(reinterpret_cast<char*>(&reservation), sizeof(Reservation))) {
        // At the end already or error
        return false; 
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
     return true;
}
void ReservationASM::seekToBeginning() {
    if (file.is_open()) {
        file.clear();  // Clear any EOF or fail flags
        //returning to the beggining
        file.seekg(0, std::ios::beg);
    }
}
int ReservationASM::getCurrentID() {
    file.clear();
    //finding the index of current file pointer
    std::streampos size = file.tellg();
    return static_cast<int>(size / sizeof(Reservation));
}