#include "Bus.h"

Bus::Bus(unsigned int id, unsigned int line){
  // INITIALISATION CODE GOES IN HERE
    orderInLine = id;
    lineId = line;
}

////////////////////////////////
// get methods
///////////////////////////////
unsigned int Bus::getBusOrderInLine() const{
  return orderInLine;
}

unsigned int Bus::getDriverId() const{
  return driverId;
}

unsigned int Bus::getLineId() const{
  return lineId;
}

vector<Shift> Bus::getSchedule() const{
  return schedule;
}


//////////////////////////////
// set methods
/////////////////////////////

void Bus::setDriverId(int id) {
    driverId = id;
};

////////////////////////////
// other methods
///////////////////////////
