/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file utils.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief collection of helper functions
 * @version 1
 * @date 2025-07-08
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
};