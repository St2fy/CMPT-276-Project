/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file utils.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @handles initialization, shut down, validation, and queries
 * @version 2
 * @date 2025-08-04
 * 
*/

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
#include <iostream>
#include <fstream>

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
    Sailing sailing = Sailing::querySailing(sailingID);
    // Check if sailing was found by verifying the sailingID is not empty
    return strlen(sailing.getSailingID()) > 0;
}

Sailing* Utils::querySailing(const char* sailingID) {
    Sailing sailing = Sailing::querySailing(sailingID);
    // Check if sailing was found
    if (strlen(sailing.getSailingID()) > 0) {
        return new Sailing(sailing);
    }
    return nullptr;
}

Vessel* Utils::queryVessel(const char* vessel) {
    Vessel vesselObj = Vessel::queryVessel(vessel);
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

void Utils::printAllDataFiles() {
    const int BAR_LENGTH = 60;
    
    // Helper function to print a separator bar
    auto printBar = [](int length, char c = '=') {
        for (int i = 0; i < length; i++) {
            std::cout << c;
        }
        std::cout << std::endl;
    };
    
    printBar(BAR_LENGTH);
    std::cout << "                    DATA FILES CONTENTS" << std::endl;
    printBar(BAR_LENGTH);
    
    // Print vessels data
    std::cout << "\nVESSELS:" << std::endl;
    printBar(BAR_LENGTH, '-');
    VesselASM::seekToBeginning();
    Vessel vessel;
    int vesselCount = 0;
    while (VesselASM::getNextVessel(vessel)) {
        std::cout << "Vessel #" << ++vesselCount << ":" << std::endl;
        std::cout << "  Name: " << vessel.getName() << std::endl;
        std::cout << "  LCLL Capacity: " << vessel.getLCLLCap() << " meters" << std::endl;
        std::cout << "  HCLL Capacity: " << vessel.getHCLLCap() << " meters" << std::endl;
        std::cout << "  Passenger Capacity: " << vessel.getPassengerCap() << std::endl;
        std::cout << std::endl;
    }
    if (vesselCount == 0) {
        std::cout << "  No vessels found." << std::endl;
    }
    
    // Print vehicles data  
    std::cout << "\nVEHICLES:" << std::endl;
    printBar(BAR_LENGTH, '-');
    VehicleASM::seekToBeginning();
    Vehicle vehicle;
    int vehicleCount = 0;
    while (VehicleASM::getNextVehicle(vehicle)) {
        std::cout << "Vehicle #" << ++vehicleCount << ":" << std::endl;
        std::cout << "  Length: " << vehicle.length << " meters" << std::endl;
        std::cout << "  Height: " << vehicle.height << " meters" << std::endl;
        std::cout << "  Special: " << (isSpecialVehicle(vehicle.length, vehicle.height) ? "Yes" : "No") << std::endl;
        std::cout << std::endl;
    }
    if (vehicleCount == 0) {
        std::cout << "  No vehicles found." << std::endl;
    }
    
    // Print sailings data
    std::cout << "\nSAILINGS:" << std::endl;
    printBar(BAR_LENGTH, '-');
    SailingASM::seekToBeginning();
    Sailing sailing;
    int sailingCount = 0;
    while (SailingASM::getNextSailing(sailing)) {
        std::cout << "Sailing #" << ++sailingCount << ":" << std::endl;
        std::cout << "  Sailing ID: " << sailing.getSailingID() << std::endl;
        std::cout << "  Vessel Name: " << sailing.getVesselName() << std::endl;
        std::cout << "  Passengers: " << sailing.getPassengers() << std::endl;
        std::cout << "  LCLL Used: " << sailing.getLCLLUsed() << " meters" << std::endl;
        std::cout << "  HCLL Used: " << sailing.getHCLLUsed() << " meters" << std::endl;
        std::cout << std::endl;
    }
    if (sailingCount == 0) {
        std::cout << "  No sailings found." << std::endl;
    }
    
    // Print reservations data
    std::cout << "\nRESERVATIONS:" << std::endl;
    printBar(BAR_LENGTH, '-');
    ReservationASM::seekToBeginning();
    Reservation reservation;
    int reservationCount = 0;
    while (ReservationASM::getNextReservation(reservation)) {
        std::cout << "Reservation #" << ++reservationCount << ":" << std::endl;
        std::cout << "  License Plate: " << reservation.getLicense() << std::endl;
        std::cout << "  Sailing ID: " << reservation.getSailingID() << std::endl;
        std::cout << "  Phone Number: " << reservation.getPhoneNumber() << std::endl;
        std::cout << "  Vehicle Length: " << reservation.getVehicle().length << " meters" << std::endl;
        std::cout << "  Vehicle Height: " << reservation.getVehicle().height << " meters" << std::endl;
        std::cout << "  Special Vehicle: " << (reservation.getSpecial() ? "Yes" : "No") << std::endl;
        std::cout << "  Checked In: " << (reservation.getOnBoard() ? "Yes" : "No") << std::endl;
        std::cout << std::endl;
    }
    if (reservationCount == 0) {
        std::cout << "  No reservations found." << std::endl;
    }
    
    printBar(BAR_LENGTH);
    std::cout << "Summary: " << vesselCount << " vessels, " << vehicleCount << " vehicles, " 
              << sailingCount << " sailings, " << reservationCount << " reservations" << std::endl;
    printBar(BAR_LENGTH);
}