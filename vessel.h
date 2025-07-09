/**
 * @file vessel.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief 
 * @version 1
 * @date 2025-07-08
 * 
*/

class Vessel {
private: 
    char name[26];
    double LCLLCapacity;
    double HCLLCapacity;
    int passengerCapacity;

    Vessel();
    Vessel(char[], double, double);
    ~Vessel();
    char* to_string();

public:
    Vessel createVessel();
    void queryVessel();


};