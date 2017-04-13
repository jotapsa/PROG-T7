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
void manageLineMenu (appState &state, std::vector<Line> &lines);
void editLineMenu (std::vector<Line> &lines, unsigned int lineIndex);

#endif // __MENU_H
