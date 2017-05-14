#pragma once

//=================================
// include guard
#ifndef __COMPANY_H
#define __COMPANY_H

//=================================
// forward declared dependencies
#include "Driver.h"
#include "Line.h"

//=================================
// included dependencies
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Company{
 private:
  string name;
  vector<Driver> drivers;
  vector<Line> lines;
    string fichCondutores,fichLinhas;
 public:
    Company(string nome, string fichCondutores, string fichLinhas);

  // get methods
    string getNome() const;
    vector<Line> getLines() const;
    vector<Driver> getDrivers() const;

  // set methods

  // other methods
    static bool sort_linha (Line i,Line j);
    void ordenarLinhas();
    static bool sort_condutor (Driver i,Driver j);
    void ordenarCondutores();
    void printLines();
    void printDrivers();
    bool checkForLine(unsigned int ID);
    int newLine(bool *changed);
    int displayLines(std::string Title);
    int changeLine(bool *changed);
    int removeLine(bool *changed);
    bool checkForDriver(unsigned int id);
    int newDriver(bool *changed);
    int displayDrivers();
    int changeDriver(bool *changed);
    int removeDriver(bool *changed);
    int printSchedules();
    static bool sort_paragem (std::string i,std::string j);
    void ordenarParagens();
    int stopSchedule();
    int searchTrip();
    void updateLines();
    void updateDrivers();
    void generateShifts();
    void resetLineShifts();
    void resetDriverShifts();
    void printShifts();
    void printLineShift(int bus);
    void printDriverShift();
};

#endif
