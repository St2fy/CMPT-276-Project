class Vehicle {
private: 
    char license[11];
    char phone[15];
    unsigned int height;
    unsigned int length;


public:
    Vehicle();
    Vehicle(char[], char[], unsigned int, unsigned int);
    ~Vehicle();
    char* to_string();



};