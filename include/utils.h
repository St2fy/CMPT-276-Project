/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file utils.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief collection of helper functions
 * @version 2
 * @date 2025-08-04
 * 
*/
#pragma once
#include <string>
#include <vector>

// Forward declarations
class Reservation;
class Sailing;
class Vessel;
class Utils {
public:
    /**----------------------------------------------
     * startup function
     */
    static void init();

    /**----------------------------------------------
     * shutdown function
     */
    static void shutdown();
    /**----------------------------------------------
     * creates a sailing ID string from terminal, day, and hour
     * @param terminal
     * @param day
     * @param hour
     * @return std::string - the sailing ID in the format "terminal-day-hour"
     */
    static std::string makeSailingID(std::string terminal, std::string day, std::string hour);

    // Query utility functions
    /**----------------------------------------------
     * checks if a license plate exists in any reservation
     * @param license
     * @return bool - true if license exists, false otherwise
     */
    static bool queryLicense(const char* license);

    /**----------------------------------------------
     * finds a reservation by license plate
     * @param license
     * @return Reservation* - pointer to reservation if found, nullptr otherwise
     */
    static Reservation* queryReservation(const char* license);

    /**----------------------------------------------
     * finds all reservations by phone number
     * @param phone
     * @return std::vector<Reservation*> - vector of reservation pointers
     */
    static std::vector<Reservation*> queryReservationsByPhone(const char* phone);

    /**----------------------------------------------
     * checks if a sailing exists
     * @param sailingID
     * @return bool - true if sailing exists, false otherwise
     */
    static bool validSailing(const char* sailingID);

    /**----------------------------------------------
     * finds a sailing by ID
     * @param sailingID
     * @return Sailing* - pointer to sailing if found, nullptr otherwise
     */
    static Sailing* querySailing(const char* sailingID);

    /**----------------------------------------------
     * finds a vessel by name
     * @param vessel
     * @return Vessel* - pointer to vessel if found, nullptr otherwise
     */
    static Vessel* queryVessel(const char* vessel);

    /**----------------------------------------------
     * determines if a vehicle is considered special based on dimensions
     * @param length - vehicle length in meters
     * @param height - vehicle height in meters
     * @return bool - true if vehicle is special (>2m height OR >7m length), false otherwise
     */
    static bool isSpecialVehicle(float length, float height);

    /**----------------------------------------------
     * queries the sailing space availability for a vehicle
     * @param sailingID - the sailing to check
     * @param length - vehicle length in meters
     * @param height - vehicle height in meters
     * @return bool - true if space is available, false otherwise
     */
    static bool querySailingSpace(const char* sailingID, float length, float height);

    /**----------------------------------------------
     * gets a specific range of sailings from the data store (memory efficient)
     * @param startIndex - starting index (0-based)
     * @param count - number of sailings to read
     * @return std::vector<Sailing>* - vector containing only the requested sailings
     */
    static std::vector<Sailing>* getSailings(int startIndex, int count);

    /**----------------------------------------------
     * checks if there are more sailings available beyond a given index
     * @param index - the index to check after
     * @return bool - true if more sailings exist, false otherwise
     */
    static bool hasMoreSailings(int index);

    /**----------------------------------------------
     * gets the list of all vessels
     * @return std::vector<Vessel>* - vector containing all vessels
     */
    static std::vector<Vessel>* getVessels();

    /**----------------------------------------------
     * prints the contents of all data files for debugging/inspection
     */
    static void printAllDataFiles();
};