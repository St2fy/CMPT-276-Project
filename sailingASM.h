#pragma once
#include <fstream>
#include <string>
#include "sailing.h"

class SailingASM {
public:
    static void initialize();
    static void shutdown();
    static void addSailing(const Sailing& sailing);
    static bool getNextSailing(Sailing& sailing);
    static void seekToBeginning();
    static int getCurrentID();
private:
    static std::fstream file;
    static const std::string filename;
};