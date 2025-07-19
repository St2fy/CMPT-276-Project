/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file Reservation.h
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
    Vehicle vehicle;

    Reservation();
    Reservation(char* license, char* sailingID, char* phoneNumber);
    ~Reservation();
    char* to_string();

    
public:
    /**----------------------------------------------
     * creates a reservation for a sailing, safe against duplicate reservations
     * @param license
     * @param sailingID
     * @param phoneNumber
     * @return Reservation
     */
    Reservation createReservation(char* license, char* sailingID, char* phoneNumber);

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
    Reservation queryReservation(char* sailingID, char* phoneNumber);
    /**----------------------------------------------
     * startup function
     */
    void init();

    /**----------------------------------------------
     * shutdown function
     */
    void shutdown();
};



