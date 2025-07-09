#pragma once
#include <fstream>
#include <string>
#include "reservation.h"

class VehicleASM {
public:
    static void init();
    static void shutdown();
    static void addVehicle(const Vehicle& vehicle);
    static bool getNextVehicle(Vehicle& vehicle);
    static void seekToBeginning();
    static int getCurrentID();
private:
    static std::fstream file;
    static const std::string filename;
};