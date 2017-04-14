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
  Driver () {};
  Driver (unsigned int id);
  void setFromString (std::string &driverString);

  //getters
  unsigned int getId () const {return id;};
  std::string getName () const {return name;};
  unsigned int getMaxShiftHours () {return maxShiftHours;};
  unsigned int getMaxWeekHours () {return maxWeekHours;};
  unsigned int getMinBetweenShiftHours () {return minBetweenShiftHours;};
  //setters
  void setId (unsigned int id) {this->id = id;};
  void setName (std::string name) {this->name = name;};
  void setMaxShiftHours (unsigned int maxShiftHours) {this->maxShiftHours = maxShiftHours;};
  void setMaxWeekHours (unsigned int maxWeekHours) {this->maxWeekHours = maxWeekHours;};
  void setMinBetweenShiftHours (unsigned int minBetweenShiftHours) {this->minBetweenShiftHours = minBetweenShiftHours;};

};

std::vector<Driver> readDriversFile (std::string driversFile);

void printDrivers (const std::vector<Driver> &drivers);
void createDriver (std::vector<Driver> &drivers);
unsigned int getDriverIndex(const std::vector<Driver> &drivers);

void changeDriverId (std::vector<Driver> &drivers, unsigned int driverIndex);
void changeDriverName (std::vector<Driver> &drivers, unsigned int driverIndex);
void changeDriverMaxShiftHours (std::vector<Driver> &drivers, unsigned int driverIndex);
void changeDriverMaxWeekHours (std::vector<Driver> &drivers, unsigned int driverIndex);
void changeDriverMinBetweenShiftHours (std::vector<Driver> &drivers, unsigned int driverIndex);

void removeDriver (std::vector<Driver> &drivers, unsigned int driverIndex);

void storeDrivers (std::string filePath, const std::vector<Driver> &drivers);

#endif // __DRIVER_H
