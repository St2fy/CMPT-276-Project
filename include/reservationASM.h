/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file reservationASM.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handle IO file for reservations
 * @version 2
 * @date 2025-08-04
 * 
*/

#pragma once
#include <fstream>
#include <string>
#include "reservation.h"

class ReservationASM {
public:
    /**----------------------------------------------
     * startup function
     */
    static void init();

    /**----------------------------------------------
     * shutdown function
     */
    static void shutdown();
    static void addReservation(const Reservation& reservation);
    static bool getNextReservation(Reservation& reservation);
    static bool overwriteReservation(const Reservation& reservation, int index);
    static void seekToBeginning();
    static int getCurrentID();
private:
    static std::fstream file;
    static const std::string filename;
};