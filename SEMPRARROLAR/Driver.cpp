#include "Driver.h"

Driver::Driver(string textLine){
    std::vector<std::string> splitStrings(split(textLine,';'));
    std::istringstream inSStream;
    
    //Check the size
    if (splitStrings.size() != 5){
        return;
    }
    
    //Already know the first element is the id
    inSStream.str(splitStrings.at(0));
    inSStream.clear();
    inSStream >> id;
    
    //Second element is the name
    name = splitStrings.at(1);
    
    //Maximum hours per shift
    inSStream.str(splitStrings.at(2));
    inSStream.clear();
    inSStream >> maxHours;
    
    //Maximum hours per week
    inSStream.str(splitStrings.at(3));
    inSStream.clear();
    inSStream >> maxWeekWorkingTime;
    
    //Minimin hours between shifts
    inSStream.str(splitStrings.at(4));
    inSStream.clear();
    inSStream >> minRestTime;
}

Driver::Driver(){
    
}

//////////////
// get methods
//////////////

unsigned int Driver::getId() const{
  return id;
}

string Driver::getName() const{
  return name;
}

unsigned int Driver::getMaxHours() const{
  return maxHours;
}

unsigned int Driver::getMaxWeekWorkingTime() const{
  return maxWeekWorkingTime;
}

unsigned int Driver::getMinRestTime() const{
  return minRestTime;
}

vector<Shift> Driver::getShifts() const{
  return shifts;
}

//////////////
// set methods
//////////////
void Driver::setId (unsigned int id) {
    this->id = id;
}
void Driver::setName (std::string name) {
    this->name = name;
}
void Driver::setMaxHours (unsigned int maxHours) {
    this->maxHours = maxHours;
}
void Driver::setMaxWeekWorkingTime (unsigned int maxWeekWorkingTime) {
    this->maxWeekWorkingTime = maxWeekWorkingTime;
}
void Driver::setMinRestTime (unsigned int minRestTime) {
    this->minRestTime = minRestTime;
}

//////////////
// other methods
//////////////

