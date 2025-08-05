/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file vessel.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handles vessel operations
 * @version 1
 * @date 2025-07-08
 * 
*/
#pragma once
class Vessel {
private: 
    char name[26];
    float LCLLCapacity;
    float HCLLCapacity;
    int passengerCapacity;

    char* to_string();

public:
    Vessel();
    Vessel(char* name, float LCLL, float HCLL);
    ~Vessel();
    char* getName();
    float getLCLLCap();
    float getHCLLCap();
    int getPassengerCap();
    /**----------------------------------------------
     * creates a vessel, safe against duplicate vessels
     * @param name
     * @param LCLL
     * @param HCLL
     * @return Vessel
     */
    static Vessel* createVessel(char* name, float LCLL, float HCLL);

    /**----------------------------------------------
     * initiates a search for a vessel
     * @param name
     * @return Vessel
     */
    static Vessel queryVessel(char* name);

    /**----------------------------------------------
     * startup function
     */
    static void init();

    /**----------------------------------------------
     * shutdown function
     */
    static void shutdown();


};