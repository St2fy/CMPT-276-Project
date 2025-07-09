/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file vessel.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief handles vessel operations
 * @version 1
 * @date 2025-07-08
 * 
*/

class Vessel {
private: 
    char name[26];
    float LCLLCapacity;
    float HCLLCapacity;
    int passengerCapacity;

    Vessel();
    Vessel(char* name, float LCLL, float HCLL);
    ~Vessel();
    char* to_string();

public:
    /**----------------------------------------------
     * creates a vessel, safe against duplicate vessels
     * @param name
     * @param LCLL
     * @param HCLL
     * @return Vessel
     */
    Vessel createVessel(char* name, float LCLL, float HCLL);

    /**----------------------------------------------
     * initiates a search for a vessel
     * @param name
     * @return Vessel
     */
    Vessel queryVessel(char* name);

    /**----------------------------------------------
     * startup function
     */
    void init();

    /**----------------------------------------------
     * shutdown function
     */
    void shutdown();


};