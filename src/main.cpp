/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file main.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handles startup and shutdown entry to the menu
 * @version 2
 * @date 2025-08-05
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
#include <iostream>
#include <filesystem>
#include <fstream>

// Forward declaration for menu function
void handleMenu();

void preloadData() {
    // First shutdown to flush any existing data to files
    Utils::shutdown();
    
    // Clear all existing data files
    std::remove("data/vessels.dat");
    std::remove("data/vehicles.dat");
    std::remove("data/sailings.dat");
    std::remove("data/reservations.dat");
    
    // Also clear any files that might be in the root directory
    std::remove("vessels.dat");
    std::remove("vehicles.dat");
    std::remove("sailings.dat");
    std::remove("reservations.dat");

    // Initialize with clean state
    Utils::init();
    
    Utils::shutdown();
    Utils::init();
    
    // Create ferry vessels
    Vessel::createVessel("Coastal Runner", 111.0f, 222.0f); 
    Vessel::createVessel("Island Voyager", 0.0f, 70.0f); 
    Vessel::createVessel("Wave Dancer", 15.0f, 59.0f); 
    
    Vessel* coastalRunner = Utils::queryVessel("Coastal Runner");
    Vessel* islandVoyager = Utils::queryVessel("Island Voyager");
    Vessel* waveDancer = Utils::queryVessel("Wave Dancer");
    
    // Sailings for Coastal Runner
    Sailing::createSailing("Coastal Runner", "ABC-01-07", 0.0f, 0.0f, coastalRunner);
    Sailing::createSailing("Coastal Runner", "DEF-15-13", 0.0f, 0.0f, coastalRunner);
    
    // Sailings for Island Voyager
    Sailing::createSailing("Island Voyager", "LMN-27-18", 0.0f, 0.0f, islandVoyager);
    Sailing::createSailing("Island Voyager", "XYZ-28-24", 0.0f, 0.0f, islandVoyager);
    Sailing::createSailing("Island Voyager", "QWE-10-09", 0.0f, 0.0f, islandVoyager);
    
    // Sailing for Wave Dancer
    Sailing::createSailing("Wave Dancer", "RTY-03-01", 0.0f, 0.0f, waveDancer);
    
    delete coastalRunner;
    delete islandVoyager;
    delete waveDancer;
    
    // Create reservations
    
    // Reservation 1: Normal vehicle on ABC-01-07
    Vehicle vehicle1 = {5.0f, 1.8f}; 
    Reservation::createReservation("BC1234", "ABC-01-07", "604-555-1234", vehicle1, false);
    
    // Reservation 2: Special vehicle on ABC-01-07 
    Vehicle vehicle2 = {60.0f, 4.1f}; 
    Reservation::createReservation("AB-TRK-222", "ABC-01-07", "604-787-8888", vehicle2, true);
    
    // Reservation 3: Normal vehicle on DEF-15-13
    Vehicle vehicle3 = {4.5f, 1.7f}; 
    Reservation::createReservation("BC5678", "DEF-15-13", "604-777-8888", vehicle3, false);
}

/**----------------------------------------------
 * Clears all data files and initializes with empty system
 */
void initializeEmptySystem() {
    // Clear all existing data files
    std::remove("data/vessels.dat");
    std::remove("data/vehicles.dat");
    std::remove("data/sailings.dat");
    std::remove("data/reservations.dat");
    
    // Also clear any files that might be in the root directory
    std::remove("vessels.dat");
    std::remove("vehicles.dat");
    std::remove("sailings.dat");
    std::remove("reservations.dat");
    
    // Initialize the system with empty files
    Utils::init();
}

int main() {
    // Toggle between modes by commenting/uncommenting one of these lines:
    preloadData();              // DEFAULT: Start with test data (vessels, sailings, reservations)
    // initializeEmptySystem();  // ALTERNATE: Start with empty data files
    
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