#include "utils.h"
#include "reservationASM.h"
#include "vesselASM.h"
#include "vehicleASM.h"
#include "sailingASM.h"
#include <string>

void Utils::init() {
    ReservationASM::init();
    VesselASM::init();
    VehicleASM::init();
    SailingASM::init();
}

void Utils::shutdown() {
    ReservationASM::shutdown();
    VesselASM::shutdown();
    VehicleASM::shutdown();
    SailingASM::shutdown();
}

std::string Utils::makeSailingID(std::string terminal, std::string day, std::string hour) {
    return terminal + "-" + day + "-" + hour;
}