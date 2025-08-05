/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file menu.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handles the user interface
 * @version 2
 * @date 2025-08-04
 * 
*/
#include "reservation.h"
#include "sailing.h"
#include "sailingASM.h"
#include "utils.h"
#include "vessel.h"
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <vector>
#include <sstream>

const int BAR_LENGTH = 40; // constants for the length of the - bar in the menu
const float LENGTH_RATE = 10; // !!!temporary rate for vehicle cost per meter of length
enum Result { Success, Failure, Exit, Restart }; // enum for the result of the menu operations, more readable than integers

void printBar(int length) {
    for (int i = 0; i < length; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

/**
 * Checks if a reservation can be made for a specific sailing
 * Validates space availability considering special vehicles (>2m height OR >7m length)
 * 
 * @param sailingID - the sailing to check
 * @param phoneNumber 
 * @param licenseNumber 
 * @param length 
 * @param height 
 * @return true if reservation can be made, false otherwise
 */
bool checkReservation(const char* sailingID, const char* phoneNumber, const char* licenseNumber, float length, float height) {
    if (!Utils::querySailingSpace(sailingID, length, height)) {
        return false;
    }
    //make the reservation
    return true;
}
// temporary function to calculate a fare, refactor to Reservation
float calculateFare(const Reservation* res) {
    return 40.5;
}

/**
 * helper function for handleSailingReport to print the lines of each sailing
 * Prints the sailing report lines from low to high index
 * 
 * @param low 
 * @param high 
 */
void printSailingReportLines(int low, int high) {
    int count = high - low; // Number of records to read
    std::vector<Sailing>* sailings = Utils::getSailings(low, count);
    
    if (sailings->empty()) {
        std::cout << std::endl << "End of Sailings" << std::endl << std::endl;
        delete sailings;
        return;
    }
    
    for (size_t i = 0; i < sailings->size(); i++) {
        char day[3];
        char hour[3];
        char sailingID[9];
        strcpy(sailingID, sailings->at(i).getSailingID());
        strncpy(day, sailingID + 4, 2);
        strncpy(hour, sailingID + 7, 2);
        day[2] = '\0';
        hour[2] = '\0';
        
        // Get vessel information for capacity fractions
        Vessel* vessel = Utils::queryVessel(sailings->at(i).getVesselName());
        
        std::cout << std::left << (low + i) << std::setw(5) << ")"; // Use actual index
        std::cout << std::setw(16) << sailings->at(i).getSailingID(); 
        std::cout << std::setw(24) << sailings->at(i).getVesselName();
        std::cout << day << std::setw(3) << "d";
        std::cout << hour << std::setw(6) << "h";
        
        // Display fractions: used/capacity
        if (vessel != nullptr) {
            // Format floating point numbers with 1 decimal place
            std::ostringstream lcllStream, hcllStream;
            lcllStream << std::fixed << std::setprecision(1) << sailings->at(i).getLCLLUsed() << "/" << vessel->getLCLLCap();
            hcllStream << std::fixed << std::setprecision(1) << sailings->at(i).getHCLLUsed() << "/" << vessel->getHCLLCap();
            
            std::cout << std::setw(12) << lcllStream.str();
            std::cout << std::setw(12) << hcllStream.str() << std::endl;
        } else {
            // Fallback if vessel not found
            std::cout << std::fixed << std::setprecision(1);
            std::cout << std::setw(12) << sailings->at(i).getLCLLUsed();
            std::cout << std::setw(12) << sailings->at(i).getHCLLUsed() << std::endl;
        }
    }
    
    // If we got fewer records than requested, we've reached the end
    if (sailings->size() < static_cast<size_t>(count)) {
        std::cout << std::endl << "End of Sailings" << std::endl << std::endl;
    }
    
    delete sailings; // Clean up memory
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

    bool found = false;
    do {
        if (!found && !sailingID.empty()) {
            std::cout << "Sailing ID: " << sailingID << " not found. Try again" << std::endl;
            std::cout << "Enter Sailing ID terminal-day-hour:" << std::endl;
        }
        std::cin >> sailingID;
        found = Utils::validSailing(sailingID.c_str());
    } while (!found);
    printBar(BAR_LENGTH);
    std::cout << "Sailing " << sailingID << " found " << std::endl << std::endl;
    std::cout << "Enter Phone Number (10 digits): " << std::endl;
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
    if (!checkReservation(sailingID.c_str(), phoneNumber.c_str(), license.c_str(), std::stof(length), std::stof(height))) {
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
            {
                Vehicle vehicle;
                vehicle.length = std::stof(length);
                vehicle.height = std::stof(height);
                bool special = Utils::isSpecialVehicle(vehicle.length, vehicle.height);
                Reservation::createReservation(license.c_str(), sailingID.c_str(), phoneNumber.c_str(), vehicle, special);
            }
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
    if (Utils::validSailing(sailingID.c_str())) {
        std::cout << "Deleted Sailing " << sailingID.c_str() << std::endl;
        Sailing::deleteSailing(sailingID.c_str());
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
    bool found = Utils::queryLicense(license.c_str());
    Reservation *reservation = Utils::queryReservation(license.c_str());
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
    std::cout << "Check-in successful, collect payment and Select an Option:" << std::endl;
    std::cout << "1. Continue" << std::endl;
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
    std::cout << "Available Vessels: " << std::endl;
    std::vector<Vessel>* vessels = Utils::getVessels();
    
    if (vessels->empty()) {
        std::cout << "No vessels available. Please create a vessel first." << std::endl;
        delete vessels;
        return Failure;
    }
    
    for (size_t i = 0; i < vessels->size(); i++) {
        std::cout << i + 1 << ". " << vessels->at(i).getName() << std::endl;
    }
    std::cout << std::endl << "Select Vessel: " << std::endl;
    std::string vesselInput;
    std::cin >> vesselInput;

    int vesselIndex = atoi(vesselInput.c_str()) - 1; // Convert to 0-based index
    bool validVessel = (vesselIndex >= 0 && vesselIndex < static_cast<int>(vessels->size()));
    
    if (!validVessel) {
        std::cout << "Invalid vessel selection." << std::endl;
        delete vessels;
        return Failure;
    }
    
    // Get the actual vessel name
    std::string selectedVesselName = vessels->at(vesselIndex).getName();
    delete vessels; // Clean up memory
    
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
    std::cout << std::left << std::setw(20) << "Vessel Name: " << selectedVesselName << std::endl;
    std::cout << std::left << std::setw(20) << "Departure Terminal: " << departureTerminal << std::endl;
    std::cout << std::left << std::setw(20) << "Departure Day: " << departureDay << std::endl;
    std::cout << std::left << std::setw(20) << "Departure Hour: " << departureHour << std::endl;
    std::cout << "Confirm Create New Sailing: " << std::endl;
    std::cout << "1. Yes" << std::endl << "2. Yes and Make Another" << std::endl << "3. Restart" << std::endl << "4. Exit" << std::endl;
    std::string confirmOption;
    std::cin >> confirmOption;
    switch (atoi(confirmOption.c_str())) {
        case 1:
            {
                Vessel* vessel = Utils::queryVessel(selectedVesselName.c_str());
                Sailing::createSailing(selectedVesselName.c_str(), sailingID.c_str(), 0.0f, 0.0f, vessel);
                delete vessel; // Clean up memory
            }
            return Success;
        case 2:
            {
                Vessel* vessel = Utils::queryVessel(selectedVesselName.c_str());
                Sailing::createSailing(selectedVesselName.c_str(), sailingID.c_str(), 0.0f, 0.0f, vessel);
                delete vessel; // Clean up memory
            }
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
    std::cin.ignore(); // Clear any leftover newline from previous input
    std::getline(std::cin, vesselName);

    // check if the vessel name is > 25 characters
    while (vesselName.length() > 25) {
        printBar(BAR_LENGTH);
        std::cout << "Vessel Name is too long. Please enter a name with 25 characters or less." << std::endl;
        std::cout << "Re-enter Vessel Name: " << std::endl;
        std::getline(std::cin, vesselName);
    }

    // Check if the vessel already exists
    while (Utils::queryVessel(vesselName.c_str()) != nullptr) {
        printBar(BAR_LENGTH);
        std::cout << "Cannot Create Duplicate Vessel" << std::endl;
        std::cout << "Re-enter Vessel Name" << std::endl;
        std::getline(std::cin, vesselName);
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
            Vessel::createVessel(vesselName.c_str(), atof(LCC.c_str()), atof(HCC.c_str()));
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
        std::cout << std::left << std::setw(6) << "#)" << std::setw(16) << "SailingID" << std::setw(24) << "Vessel" << std::setw(13) << "Depart" << std::setw(12) << "LCC" << std::setw(12) << "HCC" << std::endl;
        printBar(EXTENDED_BAR_LENGTH);

        printSailingReportLines(lowIndex, highIndex);

        std::cout << "Select an Option:" << std::endl;
        printBar(EXTENDED_BAR_LENGTH);
        
        // Only show "Show Next" if there are more sailings
        if (Utils::hasMoreSailings(highIndex - 1)) {
            std::cout << "1. Show Next" << std::endl << "2. Exit" << std::endl;
        } else {
            std::cout << "1. Exit" << std::endl;
        }
        
        std::cin >> option;
        switch (atoi(option.c_str())) {
            case 1:
                if (Utils::hasMoreSailings(highIndex - 1)) {
                    lowIndex += SAILINGS_PER_REPORT;
                    highIndex += SAILINGS_PER_REPORT;
                } else {
                    return Exit;
                }
                break;
            case 2:
                return Exit;
        }
    } while (atoi(option.c_str()) != Exit);
    
    return Success;
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
    Sailing* sailing = Utils::querySailing(sailingID.c_str());
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
        delete sailing; // Clean up memory
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
    std::cin.ignore(); // Clear any leftover newline from previous input
    std::getline(std::cin, vesselName);
    Vessel* vessel = Utils::queryVessel(vesselName.c_str());
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
        delete vessel; // Clean up memory
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
    std::vector<Reservation*> reservations = Utils::queryReservationsByPhone(phoneNumber.c_str());
    printBar(BAR_LENGTH);
    std::cout << "Search > Reservation > " << phoneNumber.c_str() << std::endl << std::endl;
    // no reservations found
    if (reservations.size() == 0) {
        std::cout << "No Reservations Found" << std::endl;
        printBar(BAR_LENGTH);
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
    //some reservation(s) found
    else {
        std::cout << "Reservation(s) Found:" << std::endl;
        printBar(BAR_LENGTH);
        for (size_t i = 0; i < reservations.size(); i++) {
            std::cout << std::left << std::setw(18) << "Sailing ID:" << reservations[i]->getSailingID() << std::endl;
            std::cout << std::left << std::setw(18) << "Licence Plate:" << reservations[i]->getLicense() << std::endl;
            // Display vehicle type based on special vehicle classification
            bool isSpecial = Utils::isSpecialVehicle(reservations[i]->getVehicle().length, reservations[i]->getVehicle().height);
            std::cout << std::left << std::setw(18) << "Vehicle Type:" << (isSpecial ? "Special" : "Regular") << std::endl;
            // Display check-in status
            std::cout << std::left << std::setw(18) << "Checked In:" << (reservations[i]->getOnBoard() ? "Yes" : "No") << std::endl;
            std::cout << std::endl; // Add spacing between reservations
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
    case 2: 
        do {
            result = handleSearchVessel();
        } while (result == Restart);
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
        // std::cout << "9. Print Data Files (Debug)" << std::endl;  // DISABLED: Debug option
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
                } while (result == Restart); 
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
            // case 9:  // DISABLED: Debug option
            //     Utils::printAllDataFiles();
            //     break;
            default:
                std::cout << "Invalid Selection" << std::endl;
        }
    } while (true);
}
