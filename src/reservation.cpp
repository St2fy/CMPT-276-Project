/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file reservation.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief manages reservation operations
 * @version 2
 * @date 2025-08-05
 * 
*/
#include "reservation.h"
#include "reservationASM.h"
#include "sailing.h"
#include "vehicleASM.h"
#include "utils.h"
#include <cstring>

const float VEHICLE_LENGTH_MARGIN = 0.5f; // Safety margin for vehicle length in meters

Reservation::Reservation() {
    license[0] = '\0';
    sailingID[0] = '\0';
    phoneNumber[0] = '\0';
    onBoard = false;
    special = false;
    vehicle.height = 0.0f;
    vehicle.length = 0.0f;
}

Reservation::Reservation(const char* license, const char* sailingID, const char* phoneNumber, Vehicle vehicle, bool special) {
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

const char* Reservation::getLicense() const {
    return license;
}

const char* Reservation::getSailingID() const {
    return sailingID;
}

const char* Reservation::getPhoneNumber() const {
    return phoneNumber;
}

const Vehicle& Reservation::getVehicle() const {
    return vehicle;
}

bool Reservation::getOnBoard() const {
    return onBoard;
}

bool Reservation::getSpecial() const {
    return special;
}

void Reservation::setSpecial(bool isSpecial) {
    special = isSpecial;
}

float Reservation::calculateFare() const {
    // Example fare calculation based on vehicle length and height
    return vehicle.length * 10 + vehicle.height * 5;
}

/**----------------------------------------------
 * creates a reservation for a sailing, safe against duplicate reservations
 * @param license
 * @param sailingID
 * @param phoneNumber
 * @param vehicle
 * @param special - whether this is a special reservation (for business logic)
 * @return Reservation
 */
Reservation* Reservation::createReservation(const char* license, const char* sailingID, const char* phoneNumber, Vehicle vehicle, bool special) {
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
    
    // Update sailing capacity based on vehicle type
    Sailing sailing = Sailing::querySailing(sailingID);
    if (strlen(sailing.getSailingID()) > 0) { // Sailing found
        // Check if this is a special vehicle (height > 2.0m OR length > 7.0m)
        bool isSpecial = Utils::isSpecialVehicle(vehicle.length, vehicle.height);
        
        if (isSpecial) {
            // Special vehicle - update HCLL used
            float newHCLLUsed = sailing.getHCLLUsed() + vehicle.length + VEHICLE_LENGTH_MARGIN;
            sailing.setHCLLUsed(newHCLLUsed);
        } else {
            // Regular vehicle - update LCLL used
            float newLCLLUsed = sailing.getLCLLUsed() + vehicle.length + VEHICLE_LENGTH_MARGIN;
            sailing.setLCLLUsed(newLCLLUsed);
        }
        
        // Update the sailing in the file
        Sailing::updateSailing(sailingID, sailing);
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
Reservation Reservation::queryReservation(const char* sailingID, const char* phoneNumber) {
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