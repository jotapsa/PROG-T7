#include "Shift.h"

Shift::Shift(  unsigned int linha, unsigned int condutor, unsigned int autocarro, unsigned int inicio, unsigned int fim){
  
  // INITIALISATION CODE GOES IN HERE
  

}

// metodos get
unsigned int Shift::getBusLineId() const{
  return busLineId;
}

unsigned int Shift::getDriverId() const{
  return driverId;
}
unsigned int Shift::getBusOrderNumber() const{
  return busOrderNumber;
}

unsigned int Shift::getStartTime() const{
  return startTime;
}

unsigned int Shift::getEndTime() const{
  return endTime;
}

///////////////
// set methods
//////////////

unsigned int Shift::setBusLineId(unsigned int busLineId){
  this->busLineId = busLineId;
    return 0;
}

unsigned int Shift::setDriverId(unsigned int driverId){
  this->driverId = driverId;
    return 0;
}

unsigned int Shift::setBusOrderNumber(unsigned int busOrderNumber){
  this->busOrderNumber = busOrderNumber;
    return 0;
}

unsigned int Shift::setStartTime(unsigned int startTime){
  this->startTime = startTime;
    return 0;
}

unsigned int Shift::setEndTime(unsigned int endTime){
  this->endTime = endTime;
    return 0;
}
