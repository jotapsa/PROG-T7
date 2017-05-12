#include "Driver.h"

Driver::Driver(string textLine){
    std::vector<std::string> splitStrings(split(textLine,';'));
    std::istringstream inSStream;
    
    //Check the size
    if (splitStrings.size() != 5){
        return;
    }
    
    //Remover espacos no inicio
    for (unsigned int i=0; i<splitStrings.size(); i++){
        if (splitStrings.at(i).at(0) == ' '){
            splitStrings.at(i).erase (splitStrings.at(i).begin());
        }
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
    
    maxHours *= 60;
    maxWeekWorkingTime *= 60;
    minRestTime *= 60;
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
    this->maxHours = maxHours*60;
}
void Driver::setMaxWeekWorkingTime (unsigned int maxWeekWorkingTime) {
    this->maxWeekWorkingTime = maxWeekWorkingTime*60;
}
void Driver::setMinRestTime (unsigned int minRestTime) {
    this->minRestTime = minRestTime*60;
}

//////////////
// other methods
//////////////
void Driver::imprimirTurno(){
    if(shifts.size() == 0){
        std::cout << "Não tem turnos atribuídos!" << std::endl;
        wait_for_enter();
        return;
    }
    
    for(Shift s : shifts)
        std::cout << DiadaSemana(s.getStartTime()) << " -> " << hora_string(s.getStartTime()) << " <-> " << hora_string(s.getEndTime()) << " --- Autocarro " << s.getBusOrderNumber() << " Condutor -> " << s.getDriverId() << std::endl;
    wait_for_enter();
}
