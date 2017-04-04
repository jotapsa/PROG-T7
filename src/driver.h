//=================================
// include guard
#ifndef __DRIVER_H
#define __DRIVER_H

//=================================
// included dependencies
#include <string>

class Driver{
private:
    unsigned int id;
    std::string name;
    unsigned int maxShiftHours;
    unsigned int maxWeekHours;
    unsigned int minBetweenShiftHours; //Hours the driver needs to rest between shifts
public:
    void setFromString (std::string &driverString);

};


std::vector<Driver> readDriversFile ();

#endif // __DRIVER_H
