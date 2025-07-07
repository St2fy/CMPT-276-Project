#include <string>

class Reservation {
private: 
    std::string license;
    std::string sailingID;
    bool onBoard;

public:
    Reservation();
    Reservation(std::string, std::string);
    ~Reservation();
    void checkIn();
    std::string to_string();



};



