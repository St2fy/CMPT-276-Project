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
#include "utils.h"
#include "vessel.h"
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

const int BAR_LENGTH = 40;
const float LENGTH_RATE = 10;
enum Result { Success, Failure, Exit, Restart};

void printBar(int len) {
    for (int i = 0; i < len; i++) {
        std::cout << "=";
    }
    std::cout << std::endl;
}
void printEndlines(int n) {
    for (int i = 0; i < n; i++) {
        std::cout << std::endl;
    }

}
bool querySailing(const char* sailingID) {
    if (strcmp(sailingID, "pass")) {
        return true;
    }
    return false;
}
bool querySailingSpace(float length, float height) {
    return true;
}
bool checkReservation(const char* phoneNumber, const char* licenseNumber, float length, float height) {
    if (!querySailingSpace(length, height)) {
        return false;
    }
    //make the reservation
    return true;
}
void makeReservation(const char* phoneNumber, const char* licenseNumber, float length, float height) {

}

bool queryLicense(const char* license) {
    return true;
}

Reservation* queryReservation(const char* license) {
    Reservation* r = new Reservation();
    return r;
}

float calculateFare(const Reservation* res) {
    return 40.5;
}



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
        found = querySailing(sailingID.c_str());
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
void handleCancelReservation() {
    
}
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
void handleCreateSailing() {
}
void handleCreateVessel() {
}
void handleSailingReport() {
}
void handleSearch() {
}

bool attemptSailing(char* vesselName, char* departureTerminal, char* date, char* hour);
bool attemptVessel(char* vesselName, float HCLL, float LCLL);

Vessel queryVessel(char* vesselName);

bool deleteSailing(char* sailingID);

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
        std::cin >> input;

        Result result;
        switch (atoi(input.c_str())) {
            case 1:
                do {
                    result = handleCreateReservation();
                } while (result == Restart); 
                break;
            case 2:
                handleCancelReservation();
                
                break;
            case 3:
                do {
                    result = handleCheckIn();
                } while (result == Success); 
                break;
            case 4:
                handleCreateSailing();
                break;
            case 5:
                handleCreateVessel();
                break;
            case 6:
                handleSailingReport();
                break;
            case 7:
                handleSearch();
                break;
            default:
                std::cout << "Invalid Selection" << std::endl;
                exit(0);
        }

    } while (true);


}

int main() {
    handleMenu();
    return 0;
}