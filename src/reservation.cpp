/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file reservation.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief manages reservation operations
 * @version 1
 * @date 2025-07-08
 * 
*/
#include "reservation.h"
#include "reservationASM.h"
#include "sailing.h"
#include "vehicleASM.h"
#include <cstring>

const int VEHICLE_LENGTH_MARGIN = 5; // Safety margin for vehicle length in meters

Reservation::Reservation() {
    license[0] = '\0';
    sailingID[0] = '\0';
    phoneNumber[0] = '\0';
    onBoard = false;
    special = false;
    vehicle.height = 0.0f;
    vehicle.length = 0.0f;
}

Reservation::Reservation(char* license, char* sailingID, char* phoneNumber, Vehicle vehicle, bool special) {
    strcpy(this->license, license);
    strcpy(this->sailingID, sailingID);
    strcpy(this->phoneNumber, phoneNumber);
    this->vehicle = vehicle;
    this->onBoard = false;
    this->special = special;
}

Reservation::~Reservation() {
    // No dynamic memory to free
}

char* Reservation::getLicense() {
    return license;
}

char* Reservation::getSailingID() {
    return sailingID;
}

char* Reservation::getPhoneNumber() {
    return phoneNumber;
}

const Vehicle& Reservation::getVehicle() const {
    return vehicle;
}

bool Reservation::getOnBoard() {
    return onBoard;
}

bool Reservation::getSpecial() {
    return special;
}

void Reservation::setSpecial(bool isSpecial) {
    special = isSpecial;
}

float Reservation::calculateFare() {
    // Example fare calculation based on vehicle length and height
    return vehicle.length * 10 + vehicle.height * 5;
}

/**----------------------------------------------
 * creates a reservation for a sailing, safe against duplicate reservations
 * @param license
 * @param sailingID
 * @param phoneNumber
 * @param vehicle
 * @param special - whether this is a special reservation (uses HCLL)
 * @return Reservation
 */
Reservation* Reservation::createReservation(char* license, char* sailingID, char* phoneNumber, Vehicle vehicle, bool special) {
    ReservationASM::seekToBeginning();
    Reservation r(license, sailingID, phoneNumber, vehicle, special);
    while (ReservationASM::getNextReservation(r)) {
        if (strcmp(r.getSailingID(), sailingID) == 0 && strcmp(r.getPhoneNumber(), phoneNumber) == 0) {
            // Duplicate reservation found
            return nullptr; // Return a null pointer
        }
    }
    
    // Add vehicle to VehicleASM if not already exists
    VehicleASM::seekToBeginning();
    Vehicle existingVehicle;
    bool vehicleExists = false;
    while (VehicleASM::getNextVehicle(existingVehicle)) {
        if (existingVehicle.height == vehicle.height && existingVehicle.length == vehicle.length) {
            vehicleExists = true;
            break;
        }
    }
    if (!vehicleExists) {
        VehicleASM::addVehicle(vehicle);
    }
    ReservationASM::addReservation(r);
    
    // Update sailing capacity if this is a special reservation
    if (special) {
        Sailing sailing = Sailing::querySailing(sailingID);
        if (strlen(sailing.getSailingID()) > 0) { // Sailing found
            // Add vehicle length + margin to HCLL used
            float newHCLLUsed = sailing.getHCLLUsed() + vehicle.length + VEHICLE_LENGTH_MARGIN;
            sailing.setHCLLUsed(newHCLLUsed);
            
            // Update the sailing in the file
            Sailing::updateSailing(sailingID, sailing);
        }
    }
    
    return new Reservation(license, sailingID, phoneNumber, vehicle, special);
}

/**----------------------------------------------
 * sets the reservation's onBoard to true
 */
void Reservation::checkIn() {
    onBoard = true;
}

/**----------------------------------------------
 * initiates a search for a reservation
 * @param sailingID
 * @param phoneNumber
 * @return Reservation - the reservation if found
 */
Reservation Reservation::queryReservation(char* sailingID, char* phoneNumber) {
    ReservationASM::seekToBeginning();
    Reservation r;
    while (ReservationASM::getNextReservation(r)) {
        if (strcmp(r.getSailingID(), sailingID) == 0 &&
            strcmp(r.getPhoneNumber(), phoneNumber) == 0) {
            return r;
        }
    }
    return Reservation(); // not found
}

/**----------------------------------------------
 * startup function
 */
void Reservation::init() {
    ReservationASM::init();
}

/**----------------------------------------------
 * shutdown function
 */
void Reservation::shutdown() {
    ReservationASM::shutdown();
}