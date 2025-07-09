/**
 * @file sailing.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief 
 * @version 1
 * @date 2025-07-08
 * 
*/

#include "reservation.h"
class Sailing {
private: 
    char vesselName[20];
    char sailingID[9];
    float LCLLUsed;
    float HCLLUsed;
    int passengers;
    Reservation* reservations;

public:
    Sailing();
    Sailing(char* vesselName, char* sailingID, float LCLLUsed, float HCLLUsed);
    ~Sailing();
    
    char* to_string();



};