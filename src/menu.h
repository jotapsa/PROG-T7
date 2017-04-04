//=================================
// include guard
#ifndef __MENU_H
#define __MENU_H

//=================================
// forward declared dependencies
#include "line.h"

//=================================
// included dependencies
#include <vector>

void mainMenu (appState &state);
void editLineMenu (appState &state, std::vector<Line> &lines);

#endif // __MENU_H
