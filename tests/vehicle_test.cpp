#include "vehicleASM.h"
#include "vehicleASM.cpp"
#include <iostream>
#include <iomanip> // for std::setprecision
#include "reservation.h"
void clearTestFile() {
    VehicleASM::shutdown(); // Ensure file is closed
    std::ofstream ofs("vehicles.dat", std::ios::trunc | std::ios::binary);
    ofs.close();
    VehicleASM::init();
}
void printVehicle(const Vehicle& v) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Height: " << v.height << "m, Length: " << v.length << "m\n";
}

int main() {
    clearTestFile();
    std::cout << "Storage cleared. Starting tests...\n\n";
    // Initialize
    VehicleASM::init();
    std::cout << "Initial ID count: " << VehicleASM::getCurrentID() << "\n\n";

    // Test 1: Verify empty file handling
    std::cout << "=== Empty File Test ===\n";
    VehicleASM::seekToBeginning();
    Vehicle temp;
    std::cout << "getNextVehicle on empty file: " 
              << (VehicleASM::getNextVehicle(temp) ? "FAIL" : "PASS") << "\n\n";

    // Test 2: Add test vehicles
    Vehicle vehicles[] = {
        {2.5f, 4.8f},
        {3.0f, 5.2f},
        {2.8f, 4.9f}
    };

    for (auto& v : vehicles) {
        VehicleASM::addVehicle(v);
        std::cout << "Added vehicle. Current ID: " << VehicleASM::getCurrentID() << "\n";
    }

    // Test 3: Verify sequential reading
    std::cout << "\n=== Sequential Read Test ===\n";
    VehicleASM::seekToBeginning();
    int count = 0;
    while (VehicleASM::getNextVehicle(temp)) {
        std::cout << "Record " << ++count << ": ";
        printVehicle(temp);
    }
    std::cout << "Total records read: " << count << "\n\n";

    //std::cout << "Total records read: " << count << "\n\n";

    // Test 4: Verify ID consistency
    std::cout << "=== ID Verification ===\n";
    std::cout << "getCurrentID() reports: " << VehicleASM::getCurrentID() << "\n";
    std::cout << "Actual file records: " << (VehicleASM::getCurrentID() * sizeof(Vehicle)) / sizeof(Vehicle) << "\n";

    VehicleASM::shutdown();
    return 0;
}