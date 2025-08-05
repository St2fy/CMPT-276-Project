/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file sailing.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief manages sailing operations
 * @version 2
 * @date 2025-08-04
 * 
*/
#pragma once
#include "reservation.h"
#include "vessel.h"
class Sailing {
private: 
    char vesselName[26];
    char sailingID[9];
    float LCLLUsed;
    float HCLLUsed;
    int passengers;
    Vessel* vessel;
    char* to_string();

public:
    Sailing();
    /**
     * Construct a new Sailing object
     * 
     * @param vesselName 
     * @param sailingID 
     * @param LCLLUsed 
     * @param HCLLUsed 
     * @param passengers 
     * @param vessel 
     */
    Sailing(const char* vesselName, const char* sailingID, float LCLLUsed, float HCLLUsed, int passengers, Vessel* vessel);
    ~Sailing();
    const char* getSailingID() const;
    const char* getVesselName() const;
    float getHCLLUsed() const;
    float getLCLLUsed() const;
    int getPassengers() const;
    
    void setHCLLUsed(float hcllUsed);
    void setLCLLUsed(float lcllUsed);
    void setPassengers(int passengerCount);


    /**----------------------------------------------
     * creates a sailing, safe against duplicate sailings
     * @param vesselName
     * @param sailingID
     * @param LCLLUsed
     * @param HCLLUsed
     * @return Sailing
     */
    static Sailing* createSailing(const char* vesselName, const char* sailingID, float LCLLUsed, float HCLLUsed, int passengers, Vessel* vessel);

    /**----------------------------------------------
     * deletes a sailing
     * @param sailingID
     * @return bool - true if the deletion is successful false otherwise
     */
    static bool deleteSailing(const char* sailingID);

    /**----------------------------------------------
     * initiates a search for a sailing
     * @param sailingID
     * @return Sailing
     */
    static Sailing querySailing(const char* sailingID);

    /**----------------------------------------------
     * updates an existing sailing
     * @param sailingID
     * @param sailing - the updated sailing object
     * @return bool - true if the update is successful false otherwise
     */
    static bool updateSailing(const char* sailingID, const Sailing& sailing);

    /**----------------------------------------------
     * converts the sailing information to a string
     * @return string
     */
    static void init();

    /**----------------------------------------------
     * shutdown function
     */
    static void shutdown();
};