/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file test_vehicle.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @brief Tests adding and reading multiple vehicles using VehicleASM
 * @version 2
 * @date 2025-08-04
 * 
*/

#include "VehicleASM.h"
#include <iostream>
#include "reservation.h"
int main() {
    VehicleASM::init();

    // Add a few vehicles
    Vehicle v1 = {2.5f, 6.0f};
    Vehicle v2 = {3.2f, 5.5f};
    Vehicle v3 = {4.1f, 7.2f};

    VehicleASM::addVehicle(v1);
    VehicleASM::addVehicle(v2);
    VehicleASM::addVehicle(v3);

    std::cout << "Added 3 vehicles. Total count: " << VehicleASM::getCurrentID() << "\n\n";

    // Read all vehicles
    VehicleASM::seekToBeginning();
    Vehicle v;
    int index = 1;
    while (VehicleASM::getNextVehicle(v)) {
        std::cout << "Vehicle " << index++ << " - Height: " << v.height << ", Length: " << v.length << "\n";
    }

    VehicleASM::shutdown();
    return 0;
}