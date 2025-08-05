/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file vessel.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handles vessel operations
 * @version 2
 * @date 2025-08-04
 * 
*/
#pragma once
class Vessel {
private: 
    char name[26];
    float LCLLCapacity;
    float HCLLCapacity;

    char* to_string();

public:
    Vessel();
    Vessel(const char* name, float LCLL, float HCLL);
    ~Vessel();
    const char* getName() const;
    float getLCLLCap() const;
    float getHCLLCap() const;
    /**----------------------------------------------
     * creates a vessel, safe against duplicate vessels
     * @param name
     * @param LCLL
     * @param HCLL
     * @return Vessel
     */
    static Vessel* createVessel(const char* name, float LCLL, float HCLL);

    /**----------------------------------------------
     * initiates a search for a vessel
     * @param name
     * @return Vessel
     */
    static Vessel queryVessel(const char* name);

    /**----------------------------------------------
     * startup function
     */
    static void init();

    /**----------------------------------------------
     * shutdown function
     */
    static void shutdown();


};