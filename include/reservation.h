/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file reservation.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief manages reservation operations
 * @version 2
 * @date 2025-08-04
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
    char sailingID[10];
    char phoneNumber[14];
    bool onBoard;
    bool special;
    Vehicle vehicle;
    char* to_string();

public:
    Reservation(const char* license, const char* sailingID, const char* phoneNumber, Vehicle vehicle, bool special = false);
    Reservation();
    ~Reservation();
    const char* getLicense() const;
    const char* getSailingID() const;
    const char* getPhoneNumber() const;
    bool getOnBoard() const;
    bool getSpecial() const;
    void setSpecial(bool isSpecial);
    const Vehicle& getVehicle() const;
    float calculateFare() const;

    /**----------------------------------------------
     * creates a reservation for a sailing, safe against duplicate reservations
     * @param license
     * @param sailingID
     * @param phoneNumber
     * @param vehicle
     * @param special - whether this is a special reservation (uses HCLL)
     * @return Reservation
     */
    static Reservation* createReservation(const char* license, const char* sailingID, const char* phoneNumber, Vehicle vehicle, bool special = false);

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
    static Reservation queryReservation(const char* sailingID, const char* phoneNumber);

    /**----------------------------------------------
     * startup function
     */
    static void init();

    /**----------------------------------------------
     * shutdown function
     */
    static void shutdown();
};