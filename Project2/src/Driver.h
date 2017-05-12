#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Shift.h"
#include "semprarrolar.h"
#include <cmath>
#include <algorithm>


using namespace std;

class Driver{
 private:
  unsigned int id;
  string name;
  unsigned int maxHours;        // maximum duration of a shift
  unsigned int maxWeekWorkingTime;  // maximum number of hours of work in a week
  unsigned int minRestTime;     // minimum number of rest hours between shifts
  vector<Shift> shifts;         // assigned shifts
    unsigned int atualHours;
 public:
  Driver(string textLine);
  Driver();
  // get methods
  unsigned int getId() const;
  string getName() const;
  unsigned int getMaxHours() const;
  unsigned int getMaxWeekWorkingTime() const;
  unsigned int getMinRestTime() const;
  unsigned int getAtualHours() const;
  vector<Shift> getShifts() const;
    void setAtualHours(unsigned int atualHours);

    // set methods
    void setId (unsigned int id);
    void setName (std::string name);
    void setMaxHours (unsigned int maxHours);
    void setMaxWeekWorkingTime (unsigned int maxWeekWorkingTime);
    void setMinRestTime (unsigned int minRestTime);
  // other methods
    void imprimirTurno();
    void adicionarTurno(Shift *turno);
    void removerTurnosLinha(int idLinha);
    void imprimirPerfil();
    bool estadoCondutor(int start,int end);
    static bool sort_shift (Shift i,Shift j);
    void ordenarTurnos();
};
