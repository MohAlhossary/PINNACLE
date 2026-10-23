#ifndef ODO_MGR_H
#define ODO_MGR_H

#include "api.h"


class OdoMgr {

    pros::Gps &gps;

    public:
    explicit OdoMgr(pros::Gps &gps): gps(gps) {

        }
};
#endif // ODO_MGR_H
