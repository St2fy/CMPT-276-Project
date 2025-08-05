/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file reservation.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief manages reservation operations
 * @version 1
 * @date 2025-07-08
 * 
*/

#pragma once
struct Vehicle {
    float height;
    float length;
};

class Reservation {

private:
    char license[10];
    char sailingID[9];
    char phoneNumber[14];
    bool onBoard;
    bool special;
    Vehicle vehicle;
    char* to_string();

public:
    Reservation(char* license, char* sailingID, char* phoneNumber, Vehicle vehicle, bool special = false);
    Reservation();
    ~Reservation();
    char* getLicense();
    char* getSailingID();
    char* getPhoneNumber();
    bool getOnBoard();
    bool getSpecial();
    void setSpecial(bool isSpecial);
    const Vehicle& getVehicle() const;
    float calculateFare();

    /**----------------------------------------------
     * creates a reservation for a sailing, safe against duplicate reservations
     * @param license
     * @param sailingID
     * @param phoneNumber
     * @param vehicle
     * @param special - whether this is a special reservation (uses HCLL)
     * @return Reservation
     */
    static Reservation* createReservation(char* license, char* sailingID, char* phoneNumber, Vehicle vehicle, bool special = false);

    /**----------------------------------------------
     * sets the reservation's onBoard to true
     */
    void checkIn();

    /**----------------------------------------------
     * initiates a search for a reservation
     * @param sailingID
     * @param phoneNumber
     * @return Reservation - the reservation if found
     */
    static Reservation queryReservation(char* sailingID, char* phoneNumber);

    /**----------------------------------------------
     * startup function
     */
    static void init();

    /**----------------------------------------------
     * shutdown function
     */
    static void shutdown();
};