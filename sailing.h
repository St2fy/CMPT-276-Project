/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file sailing.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief manages sailing operations
 * @version 1
 * @date 2025-07-08
 * 
*/
#pragma once
#include "reservation.h"
#include "vessel.h"
class Sailing {
private: 
    char vesselName[20];
    char sailingID[9];
    float LCLLUsed;
    float HCLLUsed;
    int passengers;
    Vessel* vessel;
    
    Sailing(char* vesselName, char* sailingID, float LCLLUsed, float HCLLUsed);
    
    
    char* to_string();

public:
    Sailing();
    ~Sailing();
    char* getSailingID();
    char* getVesselName();
    float getHCLLUsed();
    float getLCLLUsed();
    int getPassengers();
    /**----------------------------------------------
     * creates a sailing, safe against duplicate sailings
     * @param vesselName
     * @param sailingID
     * @param LCLLUsed
     * @param HCLLUsed
     * @return Sailing
     */
    Sailing createSailing(char* vesselName, char* sailingID, float LCLLUsed, float HCLLUsed);

    /**----------------------------------------------
     * deletes a sailing
     * @param sailingID
     * @return bool - true if the deletion is successful false otherwise
     */
    bool deleteSailing(char* sailingID);

    /**----------------------------------------------
     * initiates a search for a sailing
     * @param sailingID
     * @return Sailing
     */
    Sailing querySailing(char* sailingID);

    /**----------------------------------------------
     * startup function
     */
    void init();

    /**----------------------------------------------
     * shutdown function
     */
    void shutdown();
};