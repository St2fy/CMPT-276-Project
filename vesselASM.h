#pragma once
#include <fstream>
#include <string>
#include "vessel.h"

class VesselASM {
public:
    static void init();
    static void shutdown();
    static void addVessel(const Vessel& vessel);
    static bool getNextVessel(Vessel& vessel);
    static void seekToBeginning();
    static int getCurrentID();
private:
    static std::fstream file;
    static const std::string filename;
};