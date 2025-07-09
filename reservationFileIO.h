#pragma once

#include <fstream>
#include <string>
#include "reservation.h"

class ReservationFileIO {
public:
    static void initialize();
    static void shutdown();

    static void addRecord(const Reservation& reservation);
    static bool getNextRecord(Reservation& reservation);
    static void seekToBeginning();

    static bool overwriteRecordAt(int index, const Reservation& reservation);
    static bool getRecordAt(int index, Reservation& reservation);

    static int recordCount();
    static int getRecordSize();

private:
    static std::fstream file;
    static const std::string filename;
};
