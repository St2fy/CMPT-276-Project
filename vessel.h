class Vessel {
private: 
    char name[20];
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