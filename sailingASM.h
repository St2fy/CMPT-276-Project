/**
 * @file sailingASM.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handle IO file for sailings
 * @version 1
 * @date 2025-07-08
 * 
*/

#pragma once
#include <fstream>
#include <string>
#include "sailing.h"

class SailingASM {
public:
    /**----------------------------------------------
     * startup function
     */
    static void init();

    /**----------------------------------------------
     * shutdown function
     */
    static void shutdown();
    static void addSailing(const Sailing& sailing);
    static bool getNextSailing(Sailing& sailing);
    static void seekToBeginning();
    static int getCurrentID();
    static void deleteSailing();
private:
    static std::fstream file;
    static const std::string filename;
};