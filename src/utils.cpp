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
    // Check if vessel was found
    if (strlen(vesselObj.getName()) > 0) {
        return new Vessel(vesselObj);
    }
    return nullptr;
}

// Vehicle utility functions
const float VEHICLE_HEIGHT_THRESHOLD = 2.0f; // vehicles above this height need HCLL space
const float VEHICLE_LENGTH_THRESHOLD = 7.0f; // vehicles above this length need HCLL space

bool Utils::isSpecialVehicle(float length, float height) {
    return (height > VEHICLE_HEIGHT_THRESHOLD) || (length > VEHICLE_LENGTH_THRESHOLD);
}

bool Utils::querySailingSpace(const char* sailingID, float length, float height) {
    // Get the sailing information
    Sailing* sailing = Utils::querySailing(sailingID);
    if (sailing == nullptr) {
        return false; // Sailing doesn't exist
    }
    
    // Get the vessel to check total capacity
    Vessel* vessel = Utils::queryVessel(sailing->getVesselName());
    if (vessel == nullptr) {
        delete sailing;
        return false; // Vessel doesn't exist
    }
    
    // Special vehicles: height > 2.0m OR length > 7.0m
    bool specialVehicle = isSpecialVehicle(length, height);
    
    bool result;
    if (specialVehicle) {
        // Special vehicle - check HCLL capacity
        float availableHCLL = vessel->getHCLLCap() - sailing->getHCLLUsed();
        result = length <= availableHCLL;
    } else {
        // Regular vehicle - check LCLL capacity  
        float availableLCLL = vessel->getLCLLCap() - sailing->getLCLLUsed();
        result = length <= availableLCLL;
    }
    
    delete sailing;
    delete vessel;
    return result;
}

// Sailing data access functions
std::vector<Sailing>* Utils::getSailings(int startIndex, int count) {
    std::vector<Sailing>* sailings = new std::vector<Sailing>;
    
    // Seek to beginning and skip to the start index
    SailingASM::seekToBeginning();
    Sailing sailing;
    
    // Skip to the starting index
    for (int i = 0; i < startIndex; i++) {
        if (!SailingASM::getNextSailing(sailing)) {
            // Reached end of file before startIndex
            return sailings; // Return empty vector
        }
    }
    
    // Read the requested number of sailings
    for (int i = 0; i < count; i++) {
        if (SailingASM::getNextSailing(sailing)) {
            sailings->push_back(sailing);
        } else {
            // Reached end of file
            break;
        }
    }
    
    return sailings;
}

bool Utils::hasMoreSailings(int index) {
    SailingASM::seekToBeginning();
    Sailing sailing;
    
    // Skip to the index + 1
    for (int i = 0; i <= index; i++) {
        if (!SailingASM::getNextSailing(sailing)) {
            return false; // Reached end of file
        }
    }
    
    return true; // There is at least one more sailing
}

std::vector<Vessel>* Utils::getVessels() {
    std::vector<Vessel>* vessels = new std::vector<Vessel>;
    
    VesselASM::seekToBeginning();
    Vessel vessel;
    
    while (VesselASM::getNextVessel(vessel)) {
        vessels->push_back(vessel);
    }
    
    return vessels;
}