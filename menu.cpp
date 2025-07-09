class Menu {
private: 


public:
    Menu();
    void runMenu();
    char* getInput();
    int handleSelection();

    bool attemptReservation(char* phoneNumber, char* licenseNumber, int length, int height);
    bool attemptSailing(char* vesselName, char* departureTerminal, char* date, char* hour);
    bool attemptVessel(char* vesselName, float HCLL, float LCLL);

    bool queryReservation(char* sailingID, char* phoneNumber);
    bool querySailing(char* sailingID);
    bool queryVessel(char* vesselName);

    bool deleteSailing(char* sailingID);

};