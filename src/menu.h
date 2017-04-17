//=================================
// include guard
#ifndef __MENU_H
#define __MENU_H

//=================================
// forward declared dependencies
#include "line.h"
#include "driver.h"

//=================================
// included dependencies
#include <vector>

void mainMenu (appState &state);

void manageLineMenu (appState &state, std::vector<Line> &lines);
void editLineMenu (std::vector<Line> &lines, unsigned int lineIndex);

void changeLineStopsMenu (Line &line);
void addLineStopMenu (Line &line);
void removeLineStopMenu (Line &line);

void manageDriverMenu (appState &state, std::vector<Driver> &drivers);
void editDriverMenu (std::vector<Driver> &drivers, unsigned int driverIndex);

void viewInfMenu (appState &state, std::vector<Line> &lines, std::vector<Driver> &drivers);
#endif // __MENU_H
