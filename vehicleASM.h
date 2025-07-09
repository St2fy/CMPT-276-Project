/**
 * @file vehicle.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handle IO file for vehicles
 * @version 1
 * @date 2025-07-08
 * 
*/

#pragma once
#include <fstream>
#include <string>
#include "reservation.h"

class VehicleASM {
public:
    /**----------------------------------------------
     * startup function
     */
    static void init();

    /**----------------------------------------------
     * shutdown function
     */
    static void shutdown();
    static void addVehicle(const Vehicle& vehicle);
    static bool getNextVehicle(Vehicle& vehicle);
    static void seekToBeginning();
    static int getCurrentID();
private:
    static std::fstream file;
    static const std::string filename;
};