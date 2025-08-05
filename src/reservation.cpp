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

Reservation::Reservation() {
    license[0] = '\0';
    sailingID[0] = '\0';
    phoneNumber[0] = '\0';
    onBoard = false;
    vehicle.height = 0.0f;
    vehicle.length = 0.0f;
}

Reservation::Reservation(char* license, char* sailingID, char* phoneNumber, Vehicle vehicle) {
    strcpy(this->license, license);
    strcpy(this->sailingID, sailingID);
    strcpy(this->phoneNumber, phoneNumber);
    this->vehicle = vehicle;
    this->onBoard = false;
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

float Reservation::calculateFare() {
    // Example fare calculation based on vehicle length and height
    return vehicle.length * 10 + vehicle.height * 5;
}

/**----------------------------------------------
 * creates a reservation for a sailing, safe against duplicate reservations
 * todo: update the corresponding sailing to add the hcll and lcll used + 5m margin and the number of passengers
 * @param license
 * @param sailingID
 * @param phoneNumber
 * @return Reservation
 */
Reservation* Reservation::createReservation(char* license, char* sailingID, char* phoneNumber, Vehicle vehicle) {
    ReservationASM::seekToBeginning();
    Reservation r(license, sailingID, phoneNumber, vehicle);
    while (ReservationASM::getNextReservation(r)) {
        if (strcmp(r.getSailingID(), sailingID) == 0 && strcmp(r.getPhoneNumber(), phoneNumber) == 0) {
            // Duplicate reservation found
            return nullptr; // Return a null pointer
        }
    }
    VehicleASM::seekToBeginning();
    while (VehicleASM::getNextVehicle(vehicle)) {
        if (!(vehicle.height == r.getVehicle().height && vehicle.length == r.getVehicle().length)) {
            VehicleASM::addVehicle(vehicle);
        }
    }
    ReservationASM::addReservation(r);
    return new Reservation(license, sailingID, phoneNumber, vehicle);
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