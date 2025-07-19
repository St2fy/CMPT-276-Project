#include "reservation.h"
#include <cstring>

    char* Reservation::getLicense() {
        return license;
    }
    char* Reservation::getSailingID() {
        return sailingID;
    }
    char* Reservation::getPhoneNumber() {
        return phoneNumber;
    }
    const Vehicle& Reservation::getVehicle() const {
        return vehicle;
    }
    Reservation::Reservation() {
        strcpy(license, "license_t");
        strcpy(sailingID, "sail_t");
        strcpy(phoneNumber, "phone_t");
        onBoard = false;
        vehicle = {4, 5};
    }
    void Reservation::checkIn() {
        onBoard = true;
    }
    /**----------------------------------------------
     * creates a reservation for a sailing, safe against duplicate reservations
     * @param license
     * @param sailingID
     * @param phoneNumber
     * @return Reservation
     */
    Reservation* createReservation(char* license, char* sailingID, char* phoneNumber);

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