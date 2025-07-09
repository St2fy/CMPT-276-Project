#pragma once

#include <fstream>
#include <string>
#include "vessel.h"

class VesselFileIO {
public:
    static void initialize();
    static void shutdown();

    static void addRecord(const Vessel& vessel);
    static bool getNextRecord(Vessel& vessel);
    static void seekToBeginning();

    static bool overwriteRecordAt(int index, const Vessel& vessel);
    static bool getRecordAt(int index, Vessel& vessel);

    static int recordCount();
    static int getRecordSize();

private:
    static std::fstream file;
    static const std::string filename;
};