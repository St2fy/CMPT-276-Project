class Vessel {
private: 
    char name[26];
    double LCLLCapacity;
    double HCLLCapacity;
    int passengerCapacity;

public:
    Vessel();
    Vessel(char[], double, double);
    ~Vessel();
    char* to_string();
};