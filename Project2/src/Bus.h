#pragma once

//=================================
// include guard
#ifndef __BUS_H
#define __BUS_H

//=================================
// forward declared dependencies
#include "Shift.h"

//=================================
// included dependencies
#include <iostream>
#include <vector>

using namespace std;

class Bus{
private:
  unsigned int orderInLine;
  unsigned int driverId;
  unsigned int lineId;
  vector<Shift> schedule;

public:
  Bus(unsigned int id, unsigned int line);

  // get methods
  unsigned int getBusOrderInLine() const;
  unsigned int getDriverId() const;
  unsigned int getLineId() const;
  vector<Shift> getSchedule() const;

  // set methods
  void setDriverId(int id);
  void setLineId(int line) const;

  // other methods

};

#endif
