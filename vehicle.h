#include <string>

class Vehicle {
private: 
    std::string license;
    std::string phone;
    unsigned int height;
    unsigned int length;


public:
    Vehicle();
    Vehicle(std::string, std::string, unsigned int, unsigned int);
    ~Vehicle();
    std::string to_string();



};