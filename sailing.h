class Sailing {
private: 
    char vesselName[25];
    char sailingID[10];
    double LCLLUsed;
    double HCLLUsed;
    int passengers;

public:
    Sailing();
    Sailing(char[], char[], double, double);
    ~Sailing();
    
    char* to_string();
};