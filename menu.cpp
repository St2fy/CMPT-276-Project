/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file menu.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handles the user interface
 * @version 1
 * @date 2025-07-08
 * 
*/
#include "reservation.h"
#include "reservation.cpp"
#include "sailing.h"
#include "sailing.cpp"
#include "utils.h"
#include "vessel.h"
#include "vessel.cpp"
#include "utils.h"
#include "utils.cpp"
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <vector>

const int BAR_LENGTH = 40; // constants for the length of the - bar in the menu
const float LENGTH_RATE = 10; // !!!temporary rate for vehicle cost per meter of length
enum Result { Success, Failure, Exit, Restart }; // enum for the result of the menu operations, more readable than integers

void printBar(int length) {
    for (int i = 0; i < length; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}
// stub functions below
/**
 * Validates the sailing ID
 * 
 * !!! This is a stub function, replace with actual validation logic
 * 
 * @param sailingID 
 * @return true 
 * @return false 
 */
bool validSailing(const char* sailingID) {
    if (strcmp(sailingID, "pass")) {
        return true;
    }
    return false;
}
/**
 * Queries the sailing space availability
 * 
 * !!! This is a stub function, replace with actual query logic
 * 
 * @param length 
 * @param height 
 * @return true 
 * @return false 
 */
bool querySailingSpace(float length, float height) {
    return true;
}
/**
 * Checks if a reservation can be made
 * 
 * !!! This is a stub function, replace with actual check logic
 * 
 * @param phoneNumber 
 * @param licenseNumber 
 * @param length 
 * @param height 
 * @return true 
 * @return false 
 */
bool checkReservation(const char* phoneNumber, const char* licenseNumber, float length, float height) {
    if (!querySailingSpace(length, height)) {
        return false;
    }
    //make the reservation
    return true;
}
/**
 * Makes a reservation
 * 
 * !!! This is a stub function, replace with actual reservation logic
 * 
 * @param phoneNumber 
 * @param licenseNumber 
 * @param length 
 * @param height 
 */
void makeReservation(const char* phoneNumber, const char* licenseNumber, float length, float height) {

}
/**
 * Makes a sailing
 * 
 * !!! This is a stub function, replace with actual sailing logic
 * 
 * @param vessel 
 * @param sailingID 
 */
void makeSailing(const char* vessel, const char* sailingID) {
    
}
/**
 * Makes a vessel
 * 
 * !!! This is a stub function, replace with actual vessel logic
 * 
 * @param vessel 
 * @param HCC 
 * @param LCC 
 */
void makeVessel(const char* vessel, float HCC, float LCC) {

}
/**
 * Queries the license information
 * 
 * !!! This is a stub function, replace with actual query logic
 * 
 * @param license 
 * @return true 
 * @return false 
 */
bool queryLicense(const char* license) {
    return true;
}
/**
 * Queries the reservation information
 * 
 * !!! This is a stub function, replace with actual query logic
 * 
 * @param license 
 * @return Reservation* 
 */
Reservation* queryReservation(const char* license) {
    Reservation* r = new Reservation();
    return r;
}
/**
 * Queries the sailing information
 * 
 * !!! This is a stub function, replace with actual query logic
 * 
 * @param sailingID 
 * @return Sailing* 
 */
Sailing* querySailing(const char* sailingID) {
    Sailing* s = new Sailing();
    return s;
}
/**
 * Queries the reservations by phone number
 * 
 * !!! This is a stub function, replace with actual query logic
 * 
 * @param phone 
 * @return std::vector<Reservation*> 
 */
std::vector<Reservation*> queryReservationsByPhone(const char* phone) {

}
/**
 * Queries the vessel information
 * 
 * !!! This is a stub function, replace with actual query logic
 * 
 * @param vessel 
 * @return Vessel* 
 */
Vessel* queryVessel(const char* vessel) {
    return nullptr;
}
// temporary function to calculate a fare, refactor to Reservation
float calculateFare(const Reservation* res) {
    return 40.5;
}
/**
 * Gets the list of vessels
 * 
 * @return std::vector<Vessel>* 
 */
std::vector<Vessel>* getVessels() {
    std::vector<Vessel>* v = new std::vector<Vessel>;
    return v;
}
/**
 * Gets the list of sailings
 * 
 * @return std::vector<Sailing>* 
 */
std::vector<Sailing>* getSailings() {
    std::vector<Sailing>* s  = new std::vector<Sailing>;
    Sailing* s1 = new Sailing();
    Sailing* s2 = new Sailing();
    s->push_back(*s1);
    s->push_back(*s2);
    return s;
}
/**
 * Deletes a sailing
 * 
 * !!! This is a stub function, replace with actual deletion logic
 * 
 * @param sailing 
 */
void deleteSailing(Sailing* sailing) {

}
// end of stub functions

/**
 * helper function for handleSailingReport to print the lines of each sailing
 * Prints the sailing report lines from low to high index
 * 
 * @param low 
 * @param high 
 */
void printSailingReportLines(int low, int high) {
    std::vector<Sailing>* sailings = getSailings();
    for (int i = low; i < high; i++) {
        if (i == sailings->size()) {
            std::cout << std::endl << "End of Sailings" << std::endl << std::endl;
            return;
        }
        char day[3];
        char hour[3];
        char sailingID[9];
        strcpy(sailingID, sailings->at(i).getSailingID());
        strncpy(day, sailingID + 4, 2);
        strncpy(hour, sailingID + 7, 2);
        day[2] = '\0';
        hour[2] = '\0';
        std::cout << std::left << i << std::setw(5) << ")";
        std::cout << std::setw(16) << sailings->at(i).getSailingID(); 
        std::cout << std::setw(24) << sailings->at(i).getVesselName();
        std::cout << day << std::setw(2) << "d";
        std::cout << hour << std::setw(2) << "h";
        // !!! add fractions once oop for vessel is done
        std::cout << std::setw(12) << sailings->at(i).getPassengers();
        std::cout << std::setw(12) << sailings->at(i).getLCLLUsed();
        std::cout << std::setw(12) << sailings->at(i).getHCLLUsed() << std::endl;
    }
    std::cout << std::endl;
}
/**
 * Handles the creation of a reservation
 * 
 * @return Result 
 */
Result handleCreateReservation() {
    printBar(BAR_LENGTH);
    std::cout << "Make a Reservation" << std::endl << std::endl;
    std::cout << "Enter Sailing ID terminal-day-hour:" << std::endl;
    std::string sailingID;

    bool found = true;
    do {
        if (!found) {
            std::cout << "Sailing ID: " << sailingID << " not found. Try again" << std::endl;
        }
        
        std::cin >> sailingID;
        found = validSailing(sailingID.c_str());
    } while (found);
    printBar(BAR_LENGTH);
    std::cout << "Sailing " << sailingID << " found " << std::endl << std::endl;
    std::cout << "Enter Phone Number dddddddddd: " << std::endl;
    std::string phoneNumber;
    std::cin >> phoneNumber;
    printBar(BAR_LENGTH);
    std::cout << "Enter License Plate (10 characters): " << std::endl;
    std::string license;
    std::cin >> license;
    printBar(BAR_LENGTH);
    std::cout << "Enter Vehicle Length in meters: " << std::endl;
    std::string length;
    std::cin >> length;
    printBar(BAR_LENGTH);
    std::cout << "Enter Vehicle Height in meters: " << std::endl;
    std::string height;
    std::cin >> height;
    if (!checkReservation(phoneNumber.c_str(), license.c_str(), std::stof(length), std::stof(height))) {
        std::cout << "Sailing is full. Reservation could not be made. " << std::endl;
        std::cout << "Select an Option: " << std::endl;
        std::cout << "1. Restart" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::string option;
        std::cin >> option;
        switch (atoi(option.c_str())) {
            case 1:
                return Restart;
            case 2:
                return Exit;
            default:
                return Exit;
        };
    }
    printBar(BAR_LENGTH);
    std::cout << "Create Reservation" << std::endl << std::endl;
    std::cout << std::left << std::setw(16) << "Sailing ID: " << sailingID << std::endl;
    std::cout << std::left << std::setw(16) << "Phone Number: " << phoneNumber << std::endl;
    std::cout << std::left << std::setw(16) << "License Number: " << license << std::endl;
    std::cout << std::left << std::setw(16) << "Length: " << length << std::endl;
    std::cout << std::left << std::setw(16) << "Height: " << height << std::endl << std::endl;
    std::cout << "Confirm Create New Reservation: " << std::endl;
    std::cout << "1. Yes" << std::endl;
    std::cout << "2. Restart" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::string confirm;
    std::cin >> confirm;
    switch (atoi(confirm.c_str())) {
        case 1:
            makeReservation(phoneNumber.c_str(), license.c_str(), std::stof(length), std::stof(height));
            return Success;
        case 2:
            return Restart;
        case 3:
            return Exit;
        default:
            return Failure;
    };

}
/**
 * Handles the cancellation of a sailing
 * 
 * @return Result 
 */
Result handleCancelSailing() {
    printBar(BAR_LENGTH);
    std::cout << "Cancel Sailing" << std::endl <<std::endl;
    std::cout << "Enter the SailingID:" << std::endl;
    std::string sailingID;
    std::cin >> sailingID;
    if (validSailing(sailingID.c_str())) {
        std::cout << "Deleted Sailing " << sailingID.c_str() << std::endl;
        deleteSailing(querySailing(sailingID.c_str()));
    }
    else {
        std::cout << "Sailing " << sailingID.c_str() << " Not Found" << std::endl;
    }
    std::cout << "Select an Option:" << std::endl;
    printBar(BAR_LENGTH);
    std::cout << "1. Restart" << std::endl << "2. Exit" << std::endl;
    std::string option;
    std::cin >> option;
    switch (atoi(option.c_str())) {
    case 1:
        return Restart;
    case 2:
        return Success;
    default:
        return Success;
    }
}
/**
 * Handles the check-in of a reservation
 * 
 * @return Result 
 */
Result handleCheckIn() {
    printBar(BAR_LENGTH);
    std::cout << "Check-In Vehicles" << std::endl << std::endl;
    std::cout << "Enter a License Number: " << std::endl;
    std::string license;
    std::cin >> license;
    bool found = queryLicense(license.c_str());
    Reservation *reservation = queryReservation(license.c_str());
    if (!found) {
        printBar(BAR_LENGTH);
        std::cout << "Check-In Vehicles > Not Found" << std::endl << std::endl;
        std::cout << "License Number " << license << " Not Found" << std::endl << std::endl;
        std::cout << "Select an Option:" << std::endl;
        std::cout << "1. Restart" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::string notFoundOption;
        std::cin >> notFoundOption;
        switch (atoi(notFoundOption.c_str())) {
            case 1:
                return Restart;
            case 2:
                return Exit;
            default:
                return Exit;
        }
    }
    printBar(BAR_LENGTH);
    std::cout << "Check-In Vehicles > LN:" << license << std::endl;
    std::cout << "Reservation " << reservation->getPhoneNumber() << " for Sailing " << reservation->getSailingID() << std::endl << std::endl;
    float fare = calculateFare(reservation);
    reservation->checkIn();
    std::cout << reservation->getVehicle().length << "m Long Vehicle @ $" << LENGTH_RATE << "/m" << std::endl << std::endl;
    std::cout << "=> Amount to be Paid: $" << fare << " <=" << std::endl << std::endl;
    std::cout << "Collect Payment and Select and Option:" << std::endl;
    std::cout << "1. Continue" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::string option;
    std::cin >> option;
    switch (atoi(option.c_str())) {
    case 1:
        return Success;
    case 2:
        return Exit;
    default:
        return Exit;
    }
}
/**
 * Handles the creation of a sailing
 * 
 * @return Result 
 */
Result handleCreateSailing() {
    printBar(BAR_LENGTH);
    std::cout << "Create New Vessel Sailing" << std::endl << std::endl;
    std::cout << "Availiable Vessels: " << std::endl;
    std::vector<Vessel>* vessels = getVessels();
    for (int i = 0; i < vessels->size(); i++) {
        std::cout << i + 1 << ". " << vessels->at(i).getName() << std::endl;
    }
    std::cout << std::endl << "Select Vessel: " << std::endl;
    std::string vesselInput;
    std::cin >> vesselInput;

    bool validVessel = false;
    for (int i = 0; i < vessels->size(); i++) {
        if (atoi(vesselInput.c_str()) == i) {
            validVessel = true;
            break;
        }
    }
    if (!validVessel) {
        // invalid selection
    }
    printBar(BAR_LENGTH);
    std::cout << "Enter Departure Terminal (3-letter code):" << std::endl;
    std::string departureTerminal;
    std::cin >> departureTerminal;

    printBar(BAR_LENGTH);
    std::cout << "Enter Departure Day (DD):" << std::endl;
    std::string departureDay;
    std::cin >> departureDay;

    printBar(BAR_LENGTH);
    std::cout << "Enter Departure Hour (DD):" << std::endl;
    std::string departureHour;
    std::cin >> departureHour;


    printBar(BAR_LENGTH);
    std::string sailingID = Utils::makeSailingID(departureTerminal, departureDay, departureHour);
    std::cout << "Create New Sailing" << std::endl;
    std::cout << "Sailing ID: " << sailingID << std::endl << std::endl;
    std::cout << std::left << std::setw(20) << "Vessel Name: " << vesselInput << std::endl;
    std::cout << std::left << std::setw(20) << "Departure Terminal: " << departureTerminal << std::endl;
    std::cout << std::left << std::setw(20) << "Departure Day: " << departureDay << std::endl;
    std::cout << std::left << std::setw(20) << "Departure Hour: " << departureHour << std::endl;
    std::cout << "Confirm Create New Sailing: " << std::endl;
    std::cout << "1. Yes" << std::endl << "2. Yes and Make Another" << std::endl << "3. Restart" << std::endl << "4. Exit" << std::endl;
    std::string confirmOption;
    std::cin >> confirmOption;
    switch (atoi(confirmOption.c_str())) {
        case 1:
            makeSailing(vesselInput.c_str(), sailingID.c_str());
            return Success;
        case 2:
            makeSailing(vesselInput.c_str(), sailingID.c_str());
            return Restart;
        case 3: 
            return Restart;
        case 4:
            return Exit;
        default:
            return Exit;
    }
}
/**
 * Handles the creation of a vessel
 * 
 * @return Result 
 */
Result handleCreateVessel() {
    printBar(BAR_LENGTH);
    std::cout << "Create New Vessel" << std::endl << std::endl;
    std::cout << "Enter Vessel Name: " << std::endl;
    std::string vesselName;
    std::cin >> vesselName;

    // Check if the vessel already exists
    while (!queryVessel(vesselName.c_str())) {
        printBar(BAR_LENGTH);
        std::cout << "Cannot Create Duplicate Vessel" << std::endl;
        std::cout << "Re-enter Vessel Name" << std::endl;
        std::cin >>vesselName;
    }

    printBar(BAR_LENGTH);
    std::cout << "Enter High Ceiling Capacity (HCC):" << std::endl;
    std::string HCC;
    std::cin >> HCC;

    printBar(BAR_LENGTH);
    std::cout << "Enter Low Ceiling Capacity (LCC):" << std::endl;
    std::string LCC;
    std::cin >> LCC;

    printBar(BAR_LENGTH);
    std::cout << "Create New Vessel" << std::endl << std::endl;
    std::cout << std::left << std::setw(16) << "Name: " << vesselName << std::endl;
    std::cout << std::left << std::setw(16) << "HCC: " << HCC << std::endl;
    std::cout << std::left << std::setw(16) << "LCC: " << LCC << std::endl;
    std::cout << "Confirm Create New Vessel:" << std::endl;
    std::cout << "1. Yes" << std::endl << "2. Restart" << std::endl << "3. Exit" << std::endl;
    std::string confirmOption;
    std::cin >> confirmOption;
    switch (atoi(confirmOption.c_str())) {
        case 1:
            makeVessel(vesselName.c_str(), atof(HCC.c_str()), atof(LCC.c_str()));
            return Success;
        case 2:
            return Restart;
        case 3: 
            return Exit;
        default:
            return Exit;
    }
}
/**
 * Handles the printing of the sailing report
 * 
 * @return Result 
 */
Result handleSailingReport() {
    const int EXTENDED_BAR_LENGTH = 90;
    const int SAILINGS_PER_REPORT = 5;
    int lowIndex = 0;
    int highIndex = 5;

    std::string option;
    do {
        printBar(EXTENDED_BAR_LENGTH);
        std::cout << "Print Sailing Report" << std::endl << std::endl;
        std::cout << std::left << std::setw(6) << "#)" << std::setw(16) << "SailingID" << std::setw(24) << "Vessel" << std::setw(8) << "Depart" << std::setw(12) << "PGC" << std::setw(12) << "LCC" << std::setw(12) << "HCC" << std::endl;
        printBar(EXTENDED_BAR_LENGTH);

        printSailingReportLines(lowIndex, highIndex);

        std::cout << "Select an Option:" << std::endl;
        printBar(EXTENDED_BAR_LENGTH);
        std::cout << "1. Print Current Selection" << std::endl << "2. Show Next" << std::endl << "3. Exit" << std::endl;
        std::cin >> option;
        switch (atoi(option.c_str())) {
            case 1:
                return Success;
            case 2:
                lowIndex += SAILINGS_PER_REPORT;
                highIndex += SAILINGS_PER_REPORT;
                break;
            case 3:
                return Exit;
        }
    } while (atoi(option.c_str()) != Exit);
}
/**
 * Handles the search of a sailing
 * 
 * @return Result 
 */
Result handleSearchSailing() {
    printBar(BAR_LENGTH);
    std::cout << "Search > Sailing" << std::endl << std::endl;
    std::cout << "Enter Sailing ID:" << std::endl;
    std::string sailingID;
    std::cin >> sailingID;
    Sailing* sailing = querySailing(sailingID.c_str());
    printBar(BAR_LENGTH);
    std::cout << "Search > Sailing > " << sailingID.c_str() << std::endl << std::endl;
    // sailing not found
    if (sailing == nullptr) {
        std::cout << "Sailing ID '" << sailingID.c_str() << "' does not exist." << std::endl << std::endl;
        std::cout << "1. Try Again" << std::endl << "2. Return to Main Menu" << std::endl;
        std::cout << "Select an Option:" << std::endl;
        std::string option;
        std::cin >> option;
        switch (atoi(option.c_str())) {
        case 1:
            return Restart;
        case 2:
            return Success;
        default:
            return Success;
        }
    }
    // sailing found
    else {
        std::cout << std::left << std::setw(18) << "Vessel Name:" << sailing->getVesselName() << std::endl;
        std::cout << std::left << std::setw(18) << "Sailing ID:" << sailing->getSailingID() << std::endl;
        std::cout << std::left << std::setw(18) << "High Ceiling Used:" << sailing->getHCLLUsed() << "m" << std::endl;
        std::cout << std::left << std::setw(18) << "Low Ceiling Used:" << sailing->getLCLLUsed() << "m" << std::endl;
        std::cout << std::left << std::setw(18) << "Passengers:" << sailing->getPassengers() << std::endl;
    }
    printBar(BAR_LENGTH);
    std::cout << "Enter any Key to Return to the Main Menu." << std::endl;
    std::string exit;
    std::cin >> exit;
    return Success;
}
/**
 * Handles the search of a vessel
 * 
 * @return Result 
 */
Result handleSearchVessel() {
    printBar(BAR_LENGTH);
    std::cout << "Search > Vessel" << std::endl << std::endl;
    std::cout << "Enter Vessel Name:" << std::endl;
    std::string vesselName;
    std::cin >> vesselName;
    Vessel* vessel = queryVessel(vesselName.c_str());
    printBar(BAR_LENGTH);
    std::cout << "Search > Vessel > " << vesselName.c_str() << std::endl << std::endl;
    // vessel not found
    if (vessel == nullptr) {
        std::cout << "Vessel '" << vesselName.c_str() << "' does not exist." << std::endl << std::endl;
        std::cout << "1. Try Again" << std::endl << "2. Return to Main Menu" << std::endl;
        std::cout << "Select an Option:" << std::endl;
        std::string option;
        std::cin >> option;
        switch (atoi(option.c_str())) {
        case 1:
            return Restart;
        case 2:
            return Success;
        default:
            return Success;
        }
    }
    // vessel found
    else {
        std::cout << std::left << std::setw(26) << "Vessel Name:" << vessel->getName() << std::endl;
        std::cout << std::left << std::setw(26) << "High Ceiling Capacity:" << vessel->getHCLLCap() << std::endl;
        std::cout << std::left << std::setw(26) << "Low Ceiling Capacity:" << vessel->getLCLLCap() << std::endl;
        std::cout << std::left << std::setw(26) << "Passenger Capacity:" << vessel->getPassengerCap() << std::endl;
    }
    printBar(BAR_LENGTH);
    std::cout << "Enter any Key to Return to the Main Menu." << std::endl;
    std::string exit;
    std::cin >> exit;
    return Success;
}
/**
 * Handles the search of a reservation
 * 
 * @return Result 
 */
Result handleSearchReservation() {
    printBar(BAR_LENGTH);
    std::cout << "Search > Reservation" << std::endl << std::endl;
    std::cout << "Enter Phone Number:" << std::endl;
    std::string phoneNumber;
    std::cin >> phoneNumber;
    std::vector<Reservation*> reservations = queryReservationsByPhone(phoneNumber.c_str());
    printBar(BAR_LENGTH);
    std::cout << "Search > Reservation > " << phoneNumber.c_str() << std::endl << std::endl;
    // no reservations found
    if (reservations.size() == 0) {
        std::cout << "No Reservations Found" << std::endl;
        printBar(BAR_LENGTH);
        std::cout << "1. Try Again" << std::endl << "Return to Main Menu" << std::endl;
        std::cout << "Select an Option:" << std::endl;
        std::string option;
        std::cin >> option;
        switch (atoi(option.c_str())) {
            case 1:
                return Restart;
            case 2:
                return Success;
            default:
                return Success;
        }
    }
    //some reservation(s) found
    else {
        std::cout << "Reservation(s) Found:" << std::endl;
        printBar(BAR_LENGTH);
        for (int i = 0; i < reservations.size(); i++) {
            std::cout << std::left << std::setw(18) << "Sailing ID:" << reservations[i]->getSailingID() << std::endl;
            std::cout << std::left << std::setw(18) << "Licence Plate" << reservations[i]->getLicense() << std::endl;
            // handle special vehicles
            std::cout << std::left << std::setw(18) << "Vehicle Type:" << reservations[i]->getVehicle().height << std::endl;
            // handle yes/no
            std::cout << std::left << std::setw(18) << "Checked In:" << reservations[i]->getOnBoard() << std::endl;
        }
    }
    printBar(BAR_LENGTH);
    std::cout << "Enter any Key to Return to the Main Menu." << std::endl;
    std::string exit;
    std::cin >> exit;
    return Success;
}
/**
 * Handles the search menu
 * Branches further into specific search options for Sailing, Vessel, or Reservation. 
 */
void handleSearch() {
    printBar(BAR_LENGTH);
    std::cout << "Search Options:" << std::endl;
    printBar(BAR_LENGTH);
    std::cout << "1. Sailing" << std::endl << "2. Vessel" << std::endl << "3. Reservation" << std::endl;
    std::string searchOption;
    std::cin >> searchOption;
    Result result;
    switch (atoi(searchOption.c_str())) {
    case 1:
        do {
            result = handleSearchSailing();
        } while (result == Restart);
        break;
        break;
    case 2: 
        do {
            result = handleSearchVessel();
        } while (result == Restart);
        break;
        break;
    case 3:
        do {
            result = handleSearchReservation();
        } while (result == Restart);
        break;
    default:
        break;
    }
}

/**
 * Handles the main menu
 * Displays the main menu options and handles user input to navigate through the application.
 * Branches into different submenus based on user selection.
 */
void handleMenu() {
    std::string input;
    do {
        printBar(BAR_LENGTH);
        std::cout << "Main Menu" << std::endl << std::endl;
        std::cout << "Select an Option:" << std::endl;
        printBar(BAR_LENGTH);
        std::cout << "1. Make a Reservation" << std::endl;
        std::cout << "2. Cancel Sailing" << std::endl;
        std::cout << "3. Check-In Reservations" << std::endl;
        std::cout << "4. Create New Sailing" << std::endl;
        std::cout << "5. Create New Vessel" << std::endl;
        std::cout << "6. Print Sailing Report" << std::endl;
        std::cout << "7. Search" << std::endl;
        std::cout << "8. Shutdown" << std::endl;
        std::cin >> input;
        Result result;
        // Handle the input and call the appropriate function based on the selection, loop based on the result of the function
        switch (atoi(input.c_str())) {
            case 1:
                do {
                    result = handleCreateReservation();
                } while (result == Restart); 
                break;
            case 2:
                do {
                    result = handleCancelSailing();
                } while (result == Restart); 
                break;
            case 3:
                do {
                    result = handleCheckIn();
                } while (result == Success); 
                break;
            case 4:
                do {
                    result = handleCreateSailing();
                } while (result == Restart);
                break;
            case 5:
                do {
                    result = handleCreateVessel();
                } while (result == Restart);
                break;
            case 6:
                handleSailingReport();
                break;
            case 7:
                handleSearch();
                break;
            case 8:
                return;
            default:
                std::cout << "Invalid Selection" << std::endl;
        }
    } while (true);
}
