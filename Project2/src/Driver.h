#pragma once

//=================================
// include guard
#ifndef __DRIVER_H
#define __DRIVER_H

//=================================
// forward declared dependencies
#include "Shift.h"

//=================================
// included dependencies
#include <vector>
#include <string>


using namespace std;

class Driver{
 private:
  unsigned int id;
  string name;
  unsigned int maxHours;        // maximum duration of a shift
  unsigned int maxWeekWorkingTime;  // maximum number of hours of work in a week
  unsigned int minRestTime;     // minimum number of rest hours between shifts
  vector<Shift> shifts;         // assigned shifts
  unsigned int workHours;
  vector<bool> workTime;

 public:
  Driver(string textLine);
  /*Don't mind me just allocating some memory*/
  Driver();

  // get methods
  unsigned int getId() const;
  string getName() const;
  unsigned int getMaxHours() const;
  unsigned int getMaxWeekWorkingTime() const;
  unsigned int getMinRestTime() const;
  unsigned int getWorkHours() const;
  vector<Shift> getShifts() const;
  vector<bool> getWorkTime() const;

  // set methods
  void setId (unsigned int id);
  void setName (std::string name);
  void setMaxHours (unsigned int maxHours);
  void setMaxWeekWorkingTime (unsigned int maxWeekWorkingTime);
  void setMinRestTime (unsigned int minRestTime);
  void setWorkHours(unsigned int workHours);

  // other methods
  void printShift();
  void addShift(Shift *shift);
  void removerTurnosLinha(int idLinha);
  void printDriver();
  bool estadoCondutor(int start,int end);
  static bool sort_shift (Shift i,Shift j);
  void ordenarTurnos();
};

#endif
