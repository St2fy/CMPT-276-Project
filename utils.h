/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file utils.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief collection of helper functions
 * @version 1
 * @date 2025-07-08
 * 
*/
#pragma once
class Utils {
private:
    Utils();
public:
    /**----------------------------------------------
     * checks if a sailingID exists
     * @param id
     * @return bool
     */
    static bool validateID(char* id);

    /**----------------------------------------------
     * generates a sailing report
     */
    static void generateReport();

    /**----------------------------------------------
     * startup function
     */
    void init();

    /**----------------------------------------------
     * shutdown function
     */
    void shutdown();


};