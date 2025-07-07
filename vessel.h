#include <string>

class Vessel {
private: 
    std::string name;
    double LCLLCapacity;
    double HCLLCapacity;

public:
    Vessel();
    Vessel(std::string, double, double);
    ~Vessel();
    std::string to_string();



};