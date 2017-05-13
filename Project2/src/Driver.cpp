#include <iostream>
#include <sstream>
#include "semprarrolar.h"
#include <cmath>
#include <algorithm>

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
    workHours=0;

    workTime.resize (TOTAL_TIME, false);
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

unsigned int Driver::getWorkHours() const{
    return workHours;
}

vector<Shift> Driver::getShifts() const{
  return shifts;
}

vector<bool> Driver::getWorkTime() const{
  return workTime;
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

void Driver::setWorkHours(unsigned int workHours){
    this->workHours = workHours;
}

//////////////
// other methods
//////////////
void Driver::printShift(){
  std::cout << "************************ " << "(" << id << ") " << name << " ************************" << std::endl;
    if((unsigned int) shifts.size() == 0){
        std::cout << "Não tem turnos atribuídos!" << std::endl;
        wait_for_enter();
        return;
    }
    for(Shift s : shifts)
        std::cout << DayofWeek(s.getStartTime()) << " -> " << hour_string(s.getStartTime()) << " <-> " << hour_string(s.getEndTime()) << " --- Autocarro " << s.getBusOrderNumber() << "| Linha -> " << s.getBusLineId() << std::endl;
    wait_for_enter();
}

void Driver::addShift(Shift *shift){
  unsigned int startTime=shift->getStartTime(), endTime=shift->getEndTime();

    shifts.push_back(*shift);
    for (unsigned int i=startTime; i<endTime; i++){
      workTime.at(i)=true;
    }
}

void Driver::removeShifts(unsigned int idLinha){
    for(unsigned int i=shifts.size()-1;i>=0;i--){
        if(shifts.at(i).getBusLineId() == idLinha){
            workHours -= (shifts.at(i).getEndTime() - shifts.at(i).getStartTime());
            shifts.erase(shifts.begin() + i);
        }
    }
}

void Driver::printDriver(){
    std::cout << "(" << id << ") " << name <<std::endl;
    std::cout << "Máximo de Horas por Turno: " << maxHours/60 << std::endl;
    std::cout << "Máximo de Horas por Semana: " << maxWeekWorkingTime/60 << std::endl;
    std::cout << "Mínimo de Horas por Descanso: " << minRestTime/60 << std::endl;
    std::cout << "Turnos Atribuídos: " << shifts.size() << std::endl;
    std::cout << "Tempo Por Atribuir : " << time_string(maxWeekWorkingTime - workHours) << std::endl;
    std::cout << std::endl;
}

bool Driver::sort_shift (Shift i,Shift j) {
    return (i.getStartTime() < j.getStartTime());
}

void Driver::sortShifts(){
    sort(shifts.begin(),shifts.end(),sort_shift);
}
