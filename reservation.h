/**
 * @file Reservation.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief 
 * @version 1
 * @date 2025-07-08
 * 
*/

class Reservation {

private: 
    char license[10];
    char sailingID[9];
    char phone[14];
    bool onBoard;

    Reservation();
    Reservation(char[], char[]);
    ~Reservation();
    char* to_string();

    struct Vehicle {
        int height;
        int length;
    };

public:
    Reservation createReservation();
    void checkIn();
    void queryReservation();
    
};



