#pragma once

#include <fstream>
#include <string>
#include "sailing.h"

class SailingASM {
public:
    static void initialize();
    static void shutdown();

    static void addRecord(const Sailing& sailing);
    static bool getNextRecord(Sailing& sailing);
    static void seekToBeginning();

    static bool overriteRecordAt(int index, const Sailing& sailing);
    static bool getRecordAt(int index, Sailing& sailing);

    static int recordCount();
    static int getRecordSize();

private:
    static std::fstream file;
    static const std::string filename;
};