class Reservation {

private: 
    char license[10];
    char sailingID[9];
    bool onBoard;

public:
    Reservation();
    Reservation(char[], char[]);
    ~Reservation();
    void checkIn();
    char* to_string();



};



