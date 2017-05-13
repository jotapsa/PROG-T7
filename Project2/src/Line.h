#pragma once

//=================================
// include guard
#ifndef __LINE_H
#define __LINE_H

//=================================
// forward declared dependencies
#include "Bus.h"
#include "Shift.h"
#include "Driver.h"

//=================================
// included dependencies
#include <vector>
#include <string>


using namespace std;

class Line{
private:
  unsigned int id;
  unsigned int freq;
  vector<string> busStopList;
  vector<int> timesList;
  vector<Bus> buses;
  vector<Shift> shifts;
  unsigned int shiftTime;

public:
  Line(string textLine);
  Line();

  // metodos get
  unsigned int getId() const;
  unsigned int getFreq() const;
  vector<string> getBusStops() const;
  vector<int> getTimings() const;
  int getIndexParagem(std::string stop) const;
  int getBusStopsSize() const;
  vector<Bus> getBuses() const;
  int getShiftTime();

  // set methods
  void setId(unsigned int ID);
  void setFreq(unsigned int Freq);

  // other methods
  void createShifts();
  void addStop (std::string stop,unsigned int pos);
  void addStop (std::string stop);
  void addTime (int time);
  bool checkStop(std::string stop);
  int tripTime(int origem,int destino,int sentido);
  void alignStop(int origem,int stop);
  void printTrip(unsigned int origem,unsigned int destino, int sentido);
  void lineSchedule();
  void generateWeekShifts(vector<Driver> *drivers);
  void resetWeekShifts(vector<Driver> *drivers,int wait);
  int change(bool *changed,vector<Driver> *drivers);
  int changeStops();
  int changeTimes();
  void printShift();
  void printLine();
};

#endif
