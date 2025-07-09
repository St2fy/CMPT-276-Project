#include "reservation.h"
class Sailing {
private: 
    char vesselName[20];
    char sailingID[9];
    double LCLLUsed;
    double HCLLUsed;
    int passengers;
    Reservation* reservations;

public:
    Sailing();
    Sailing(char[], char[], double, double);
    ~Sailing();
    
    char* to_string();



};