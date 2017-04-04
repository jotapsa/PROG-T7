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
    unsigned int getId () const {return id;};
    std::string getName () const {return name;};

};

std::vector<Driver> readDriversFile ();

void printDrivers (const std::vector<Driver> &drivers);

#endif // __DRIVER_H
