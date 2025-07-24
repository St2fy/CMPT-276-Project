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
private:
    Utils();
public:
    /**----------------------------------------------
     * checks if a sailingID exists
     * @param id
     * @return bool
     */
    static bool validateID(const char* id);

    /**----------------------------------------------
     * generates a sailing report
     */
    static void generateReport();

    /**----------------------------------------------
     * startup function
     */
    static void init();

    /**----------------------------------------------
     * shutdown function
     */
    static void shutdown();

    static std::string makeSailingID(std::string terminal, std::string day, std::string hour);
};