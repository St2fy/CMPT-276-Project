/**
 * @file utils.h
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief collection of helper functions
 * @version 1
 * @date 2025-07-08
 * 
*/

class Utils {
private:
    Utils();
public:
    static bool validateID();
    static void generateReport();

    void init();
    void shutdown();


};