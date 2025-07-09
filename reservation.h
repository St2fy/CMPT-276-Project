

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



