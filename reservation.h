class Reservation {

private: 
    char license[11];
    char sailingID[10];
    bool onBoard;

public:
    Reservation();
    Reservation(char[], char[]);
    ~Reservation();
    void checkIn();
    char* to_string();



};



