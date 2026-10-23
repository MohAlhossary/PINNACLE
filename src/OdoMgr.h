#pragma once
#include "../include/api.h"


class OdoMgr {

    pros::Gps gps;

    public:
        OdoMgr(pros::Gps gps): gps(gps) {

        }
};
