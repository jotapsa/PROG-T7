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

void clearConsole (){
	/*if (Windows)
		std::system("cls");
	else*/
		std::system("clear");
}

void nextInt(std::string string, int &number){
    do{
        std::cout << string;
        std::cin >> number;
        if(std::cin.fail()){
						std::cin.clear();
						std::cin.ignore(1000,'\n'); //clean input buffe
            continue;
        }
       return;
    }while(1);
}

void nextUnsignedInt(std::string string, unsigned int &number){
    do{
        std::cout << string;
        std::cin >> number;
        if(std::cin.fail()){
						std::cin.clear();
						std::cin.ignore(1000,'\n'); //clean input buffer
            continue;
        }
       return;
    }while(1);
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
              manageLineMenu (state, lines);
            break;
            case ManageDrivers:
              manageDriverMenu (state, drivers);
            break;
            case ViewInf:
							//
            break;
            default:
            break;
        }

    }


    return 0;
}
