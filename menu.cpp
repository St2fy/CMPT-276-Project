/**
 * @file menu.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handles the user interface
 * @version 1
 * @date 2025-07-08
 * 
*/

#include "reservation.h"
#include "sailing.h"
#include "utils.h"
#include "vessel.h"

class Menu {
private: 


public:
    Menu();
    void runMenu();
    char* getInput();
    int handleSelection();

    bool attemptReservation(char* phoneNumber, char* licenseNumber, int length, int height);
    bool attemptSailing(char* vesselName, char* departureTerminal, char* date, char* hour);
    bool attemptVessel(char* vesselName, float HCLL, float LCLL);

    Reservation queryReservation(char* sailingID, char* phoneNumber);
    Sailing querySailing(char* sailingID);
    Vessel queryVessel(char* vesselName);

    bool deleteSailing(char* sailingID);

};