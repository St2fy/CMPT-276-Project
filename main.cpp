/**************************************************************
Coding Conventions:

General
camelCase for variable and function names.
CAPITALIZED_SNAKE_CASE for constants.
4 spaces for indentation.
1 space around operators and after commas but not next to () or []
1 space between if/while/for and parentheses ex. if (x == 1)
opening brace on if/while/for statements are on the same line ex. while (y < z) {

Functions
camelCase for function names

Classes
PascalCase for class names
camelCase for fields and methods
private members first, followed by public members

Comments
use a block comment after a function signature
use single line comments after a line of code to explain what the line does
use single line comments on its own line to explain the lines of code below it

*/
#include "reservation.h"
#include "sailing.h"
#include "utils.h"
#include "vessel.h"

void init();
void shutdown();

int main() {
    init();
    

    return 0;
}