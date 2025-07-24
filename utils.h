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
};