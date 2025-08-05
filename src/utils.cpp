#include "utils.h"
#include "reservation.h"
#include "sailing.h"
#include "vessel.h"
#include "reservationASM.h"
#include "vesselASM.h"
#include "vehicleASM.h"
#include "sailingASM.h"
#include <string>
#include <cstring>

void Utils::init() {
    ReservationASM::init();
    VesselASM::init();
    VehicleASM::init();
    SailingASM::init();
}

void Utils::shutdown() {
    ReservationASM::shutdown();
    VesselASM::shutdown();
    VehicleASM::shutdown();
    SailingASM::shutdown();
}

std::string Utils::makeSailingID(std::string terminal, std::string day, std::string hour) {
    return terminal + "-" + day + "-" + hour;
}

// Query utility functions
bool Utils::queryLicense(const char* license) {
    ReservationASM::seekToBeginning();
    Reservation r;
    while (ReservationASM::getNextReservation(r)) {
        if (strcmp(r.getLicense(), license) == 0) {
            return true; // License found in reservations
        }
    }
    return false; // License not found
}

Reservation* Utils::queryReservation(const char* license) {
    ReservationASM::seekToBeginning();
    Reservation r;
    while (ReservationASM::getNextReservation(r)) {
        if (strcmp(r.getLicense(), license) == 0) {
            // Found reservation with matching license, return a copy
            return new Reservation(r.getLicense(), r.getSailingID(), r.getPhoneNumber(), 
                                 r.getVehicle(), r.getSpecial());
        }
    }
    return nullptr; // No reservation found with this license
}

std::vector<Reservation*> Utils::queryReservationsByPhone(const char* phone) {
    std::vector<Reservation*> reservations;
    ReservationASM::seekToBeginning();
    Reservation r;
    while (ReservationASM::getNextReservation(r)) {
        if (strcmp(r.getPhoneNumber(), phone) == 0) {
            // Found reservation with matching phone number, add a copy to vector
            reservations.push_back(new Reservation(r.getLicense(), r.getSailingID(), 
                                                 r.getPhoneNumber(), r.getVehicle(), r.getSpecial()));
        }
    }
    return reservations;
}

bool Utils::validSailing(const char* sailingID) {
    Sailing sailing = Sailing::querySailing(const_cast<char*>(sailingID));
    // Check if sailing was found by verifying the sailingID is not empty
    return strlen(sailing.getSailingID()) > 0;
}

Sailing* Utils::querySailing(const char* sailingID) {
    Sailing sailing = Sailing::querySailing(const_cast<char*>(sailingID));
    // Check if sailing was found
    if (strlen(sailing.getSailingID()) > 0) {
        return new Sailing(sailing);
    }
    return nullptr;
}

Vessel* Utils::queryVessel(const char* vessel) {
    Vessel vesselObj = Vessel::queryVessel(const_cast<char*>(vessel));
    // Check if vessel was found (assuming empty name means not found)
    if (strlen(vesselObj.getName()) > 0) {
        return new Vessel(vesselObj);
    }
    return nullptr;
}