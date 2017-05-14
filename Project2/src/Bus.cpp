#include "Bus.h"
#include "semprarrolar.h"

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

unsigned int Bus::getLineId() const{
  return lineId;
}

vector<Shift> Bus::getSchedule() const{
  return schedule;
}


//////////////////////////////
// set methods
/////////////////////////////

void Bus::setLineId(int line){
  this->lineId = line;
}

void Bus::setdriverIdShift(int id,unsigned int start){
  Shift *s;
  for(unsigned int i=0;i< schedule.size();i++){
    s = &schedule.at(i);
    if(s->getStartTime() == start){
      s->setDriverId(id);
      return;
    }
  }
}


////////////////////////////
// other methods
///////////////////////////

void Bus::printShift(){
  Shift *s;
  for(unsigned int i=0;i< schedule.size();i++){
    s = &schedule.at(i);
    std::cout << DayofWeek(s->getStartTime()) << " -> " << hour_string(s->getStartTime()) << " <-> " << hour_string(s->getEndTime());
    if(s->getDriverId() == 0)
      std::cout << "| Sem Condutor" << std::endl;
    else
      std::cout << "| Condutor -> " << s->getDriverId() << std::endl;
  }
  wait_for_enter();
}

void Bus::addShift(Shift *shift){
    schedule.push_back(*shift);
}
