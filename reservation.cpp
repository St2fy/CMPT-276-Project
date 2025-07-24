#include "reservation.h"
#include "reservationASM.cpp"
#include "vehicleASM.cpp"
#include <cstring>

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
void Reservation::setOnBoard(bool status) {
    onBoard = status;
}
Reservation::~Reservation() {
    // Clean up any dynamic resources if needed
}
Reservation::Reservation() {
    strcpy(license, "123456");
    strcpy(sailingID, "cde-45-56");
    strcpy(phoneNumber, "604-123-4567");
    onBoard = false;
    vehicle = {4.6f, 5.9f};
}
void Reservation::checkIn() {
    setOnBoard(true);
}
Reservation* createReservation(char* license, char* sailingID, char* phoneNumber, Vehicle vehicle) {
    ReservationASM::seekToBeginning();
    Reservation* r = new Reservation(license, sailingID, phoneNumber, vehicle);
    while (ReservationASM::getNextReservation(*r)) {
        if (strcmp(r->getSailingID(), sailingID) == 0 && strcmp(r->getPhoneNumber(), phoneNumber) == 0) {
            // Duplicate reservation found
            delete r;
            return nullptr; // Return a null pointer
        }
    }
    ReservationASM::addReservation(*r);
    return r;
}

void Reservation::checkIn() {
    setOnBoard(true);
}

Reservation* queryReservation(char* sailingID, char* phoneNumber) {
    ReservationASM::seekToBeginning();
    Reservation* r = new Reservation();
    while (ReservationASM::getNextReservation(*r)) {
        if (strcmp(r->getSailingID(), sailingID) == 0 && strcmp(r->getPhoneNumber(), phoneNumber) == 0) {
            return r;
        }
    }
    delete r; // Clean up if not found
    return nullptr;
}

Reservation* createReservation(char* license, char* sailingID, char* phoneNumber, Vehicle vehicle) {
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

Reservation* Reservation::queryReservation(char* sailingID, char* phoneNumber) {
    ReservationASM::seekToBeginning();
    Reservation r;
    while (ReservationASM::getNextReservation(r)) {
        if (strcmp(r.getSailingID(), sailingID) == 0 && strcmp(r.getPhoneNumber(), phoneNumber) == 0) {
            return new Reservation(r); // Return a copy of the found reservation
        }
    }
    return nullptr; // Return a null pointer if not found
}

Reservation::Reservation(char* license, char* sailingID, char* phoneNumber, Vehicle vehicle) {
    strcpy(this->license, license);
    strcpy(this->sailingID, sailingID);
    strcpy(this->phoneNumber, phoneNumber);
    this->vehicle = vehicle;
    this->onBoard = false;
}
float Reservation::calculateFare() {
    // Example fare calculation based on vehicle length and height
    return vehicle.length * 10 + vehicle.height * 5;
}

Reservation* createReservation(char* license, char* sailingID, char* phoneNumber, Vehicle vehicle) {
    ReservationASM::seekToBeginning();
    Reservation r(license, sailingID, phoneNumber, vehicle);
    while (ReservationASM::getNextReservation(r)) {
        if (strcmp(r.getSailingID(), sailingID) == 0 && strcmp(r.getPhoneNumber(), phoneNumber) == 0) {
            // Duplicate reservation found
            return nullptr; // Return a null pointer
        }
    }
    ReservationASM::addReservation(r);
    return new Reservation(license, sailingID, phoneNumber, vehicle);
}