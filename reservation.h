/**
 * @file Reservation.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief manages reservation operations
 * @version 1
 * @date 2025-07-08
 * 
*/

class Reservation {

private: 
    char license[10];
    char sailingID[9];
    char phoneNumber[14];
    bool onBoard;

    Reservation();
    Reservation(char* license, char* sailingID, char* phoneNumber);
    ~Reservation();
    char* to_string();

    struct Vehicle {
        int height;
        int length;
    };

public:
    Reservation createReservation(char* license, char* sailingID, char* phoneNumber);
    void checkIn();
    void queryReservation();
    void init();
    void shutdown();
};



