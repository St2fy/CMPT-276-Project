class Vehicle {
private: 
    char license[10];
    char phone[14];
    unsigned int height;
    unsigned int length;


public:
    Vehicle();
    Vehicle(char[], char[], unsigned int, unsigned int);
    ~Vehicle();
    char* to_string();



};