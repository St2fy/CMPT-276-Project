#include <string>

class Sailing {
private: 
    std::string vesselName;
    std::string sailingID;
    double LCLLUsed;
    double HCLLUsed;
    int passengers;

public:
    Sailing();
    Sailing(std::string, std::string, double, double);
    ~Sailing();
    
    std::string to_string();



};