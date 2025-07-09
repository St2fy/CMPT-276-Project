/**
 * @file Reservation.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief manages reservation operations
 * @version 1
 * @date 2025-07-08
 * 
*/
struct Vehicle {
    double height;
    double length;
};

class Reservation {

private: 
    char license[10];
    char sailingID[9];
    char phoneNumber[14];
    bool onBoard;
    Vehicle vehicle;

    Reservation();
    Reservation(char* license, char* sailingID, char* phoneNumber);
    ~Reservation();
    char* to_string();

    
public:
    Reservation createReservation(char* license, char* sailingID, char* phoneNumber);
    void checkIn();
    void queryReservation();
    void init();
    void shutdown();
};



