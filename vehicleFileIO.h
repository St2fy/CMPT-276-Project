#pragma once

#include <fstream>
#include <string>
#include "vehicle.h"

class VehicleFileIO {
public:
    static void initialize();
    static void shutdown();

    static void addRecord(const Vehicle& vehicle);
    static bool getNextRecord(Vehicle& vehicle);
    static void seekToBeginning();

    static bool overwriteRecordAt(int index, const Vehicle& vehicle);
    static bool getRecordAt(int index, Vehicle& vehicle);

    static int recordCount();
    static int getRecordSize();

private:
    static std::fstream file;
    static const std::string filename;
};
