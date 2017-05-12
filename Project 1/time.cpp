#include <string>
#include <sstream>
#include <iomanip>

#include "time.h"

Time::Time (){

}

Time::Time (unsigned int hour, unsigned int minutes){
  this->hour = hour;
  this->minutes = minutes;
}

unsigned int Time::getHour() const{
  return hour;
}

unsigned int Time::getMinutes() const{
  return minutes;
}

void Time::setHour (unsigned int hour){
  if (hour>=0 && hour<24){
    this->hour = hour;
  }
}

void Time::setMinutes (unsigned int minutes){
  if (minutes>=0 && minutes<60){
    this->minutes = minutes;
  }
}
void Time::setTime (unsigned int hour, unsigned int minutes){
  if (hour>=0 && hour<24){
    this->hour = hour;
  }
  if (minutes>=0 && minutes<60){
    this->minutes = minutes;
  }
}

void Time::addMinutes (unsigned int incMinutes){
  minutes+=incMinutes;

  while (minutes>=60){
    hour++;
    minutes-=60;
  }
  while (hour>=24){
    hour-=24;
  }
}

bool Time::before (unsigned int targetHour, unsigned int targetMinutes){
  if (hour<targetHour){
    return true;
  }
  else if (hour==targetHour && minutes < targetMinutes){
    return true;
  }
  return false;
}

std::string Time::toString (){
  std::ostringstream outSStream;

  outSStream << std::setfill('0') << std::setw(2);
  outSStream << hour;
  outSStream << ":";
  outSStream << std::setfill('0') << std::setw(2);
  outSStream << minutes;

  return outSStream.str();
}
