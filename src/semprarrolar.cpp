#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "semprarrolar.h" // for the enum
#include "line.h"
#include "driver.h"
#include "menu.h"


std::vector<std::string> split(const std::string &s, const char &delim){
	std::vector<std::string> splitStrings;
    std::istringstream inSStream(s);

    std::string partX;

    while (getline(inSStream, partX, delim)) {
        splitStrings.push_back (partX);
    }

	return  splitStrings;
}


void changeState (appState &state , appState newState){
    state = newState;
}


int main (){

    std::vector<Line> lines = readLinesFile();
    std::vector<Driver> drivers = readDriversFile ();

    appState state = Menu;

    while (state!=Quit){
        switch (state){
            case Menu:
                mainMenu(state);
            break;
            case ManageLines:
                editLineMenu (state, lines);
            break;
            case ManageDrivers:
                //
            break;
            case ViewInf:
                printDrivers (drivers);
                getchar();
                changeState (state, Menu);
            break;
            default:
            break;
        }

    }


    return 0;
}
