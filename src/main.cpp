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

// Forward declaration for menu function
void handleMenu();

int main() {
    Utils::init();
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