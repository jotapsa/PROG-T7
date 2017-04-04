//=================================
// include guard
#ifndef __SEMPRARROLAR_H
#define __SEMPRARROLAR_H

//=================================
// included dependencies
#include <vector>
#include <string>

enum appState {Menu, ManageLines, ManageDrivers, ViewInf, Quit};

/*Splits a string (passed by reference so we don't have to copy it)
into a vector of strings
*/
std::vector<std::string> split(const std::string &s, const char &delim);

void changeState (appState &state , appState newState);


#endif // __SEMPRARROLAR_H
