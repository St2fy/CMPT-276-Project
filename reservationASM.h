#pragma once
#include <fstream>
#include <string>
#include "reservation.h"

class ReservationASM {
public:
    static void initialize();
    static void shutdown();
    static void addReservation(const Reservation& reservation);
    static bool getNextReservation(Reservation& reservation);
    static void seekToBeginning();
    static int getCurrentID();
private:
    static std::fstream file;
    static const std::string filename;
};