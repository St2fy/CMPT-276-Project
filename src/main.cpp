/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file main.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handles startup and shutdown entry to the menu
 * @version 1
 * @date 2025-07-08
 * 
*/

#include "reservation.h"
#include "reservationASM.h"
#include "sailing.h"
#include "sailingASM.h"
#include "utils.h"
#include "vessel.h"
#include "vesselASM.h"
#include "vehicleASM.h"
#include <cstdio>

// Forward declaration for menu function
void handleMenu();

void preloadData() {
    // Clear all existing data files first
    std::remove("data/vessels.dat");
    std::remove("data/vehicles.dat");
    std::remove("data/sailings.dat"); 
    std::remove("data/reservations.dat"); 
    Utils::shutdown();
    Utils::init();
    
    // Create ferry vessels
    Vessel::createVessel(const_cast<char*>("Coastal Runner"), 111.0f, 222.0f); // LCLL: 111m, HCLL: 222m
    Vessel::createVessel(const_cast<char*>("Island Voyager"), 0.0f, 70.0f); // LCLL: 0m, HCLL: 70m
    Vessel::createVessel(const_cast<char*>("Wave Dancer"), 15.0f, 59.0f); // LCLL: 15m, HCLL: 59m
    
    // Create sailings
    Vessel* coastalRunner = Utils::queryVessel("Coastal Runner");
    Vessel* islandVoyager = Utils::queryVessel("Island Voyager");
    Vessel* waveDancer = Utils::queryVessel("Wave Dancer");
    
    // Sailings for Coastal Runner
    Sailing::createSailing(const_cast<char*>("Coastal Runner"), const_cast<char*>("ABC-01-07"), 0.0f, 0.0f, 0, coastalRunner);
    Sailing::createSailing(const_cast<char*>("Coastal Runner"), const_cast<char*>("DEF-15-13"), 0.0f, 0.0f, 0, coastalRunner);
    
    // Sailings for Island Voyager
    Sailing::createSailing(const_cast<char*>("Island Voyager"), const_cast<char*>("LMN-27-18"), 0.0f, 0.0f, 0, islandVoyager);
    Sailing::createSailing(const_cast<char*>("Island Voyager"), const_cast<char*>("XYZ-28-24"), 0.0f, 0.0f, 0, islandVoyager);
    Sailing::createSailing(const_cast<char*>("Island Voyager"), const_cast<char*>("QWE-10-09"), 0.0f, 0.0f, 0, islandVoyager);
    
    // Sailing for Wave Dancer
    Sailing::createSailing(const_cast<char*>("Wave Dancer"), const_cast<char*>("RTY-03-01"), 0.0f, 0.0f, 0, waveDancer);
    
    delete coastalRunner;
    delete islandVoyager;
    delete waveDancer;
    
    // Create reservations
    
    // Reservation 1: Normal vehicle on ABC-01-07
    Vehicle vehicle1 = {5.0f, 1.8f}; 
    Reservation::createReservation(const_cast<char*>("BC1234"), const_cast<char*>("ABC-01-07"), const_cast<char*>("604-555-1234"), vehicle1, false);
    
    // Reservation 2: Special vehicle on ABC-01-07 
    Vehicle vehicle2 = {60.0f, 4.1f}; 
    Reservation::createReservation(const_cast<char*>("AB-TRK-222"), const_cast<char*>("ABC-01-07"), const_cast<char*>("604-787-8888"), vehicle2, true);
    
    // Reservation 3: Normal vehicle on DEF-15-13
    Vehicle vehicle3 = {4.5f, 1.7f}; 
    Reservation::createReservation(const_cast<char*>("BC5678"), const_cast<char*>("DEF-15-13"), const_cast<char*>("604-777-8888"), vehicle3, false);
}

int main() {
    Utils::init();
    preloadData();
    handleMenu();
    Utils::shutdown();
    return 0;
}
/**************************************************************
Coding Conventions:

General 
---------------------------------------------------------------
camelCase for variable and function names.
CAPITALIZED_SNAKE_CASE for constants.
1 tab or 4 spaces for indentation.
1 space around operators and after commas but not next to () or [] ex. (a + b) and A[i]
1 space between if/while/for and parentheses ex. if (x == 1)
opening brace on if/while/for statements are on the same line ex. while (y < z) {

Classes
---------------------------------------------------------------
PascalCase for class names
camelCase for fields and methods
private members first, followed by public members

Comments
---------------------------------------------------------------
use a block comment at the top of each module
ex.
/**
 * @file main.cpp
 * @author your name
 * @brief 
 * @version 1
 * @date 2025-07-08
 * 
*/

/*
use dividing line of -'s for a total line length of 50 characters
and a block comment after a function signature to describe what the function does
ex.
/**----------------------------------------------
 * Describe the purpose of this function
 * @param x - explaination of all parameters if necessary
 * @param y - ...
 * @return z explaination of return value
 * 
/*

use single line comments after a line of code to explain what the line does
use single line comments on its own line to explain the lines of code below it

*/