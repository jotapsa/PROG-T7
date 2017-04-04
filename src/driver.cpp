#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "driver.h"
#include "semprarrolar.h"


void Driver::setFromString (std::string &driverString){
    std::vector<std::string> splitStrings(split(driverString,';'));

	std::istringstream inSStream;

	//Check the size
	if (splitStrings.size() != 5){
		//error
	}

    //Already know the first element is the id
	inSStream.str(splitStrings.at(0));
	inSStream >> id;

	//Second element is the name
	inSStream.str(splitStrings.at(1));
	inSStream >> name;

	//Maximum hours per shift
	inSStream.str(splitStrings.at(2));
	inSStream >> maxShiftHours;

	//Maximum hours per week
	inSStream.str(splitStrings.at(3));
	inSStream >> maxWeekHours;

    //Minimin hours between shifts
    inSStream.str(splitStrings.at(4));
    inSStream >> minBetweenShiftHours;
}

std::vector<Driver> readDriversFile (){
	std::ifstream fileInputStream;

    std::vector<Driver> drivers;
    std::string driverString;

    fileInputStream.open("../input/condutores.txt"); //for linux
    //fileInputStream.open("..//input//condutores.txt"); //for Windows (i think)

    if (!fileInputStream.is_open()){
        std::cerr << "Input file opening failed.\n";
        exit(1);
    }

    Driver driver;
    while (getline(fileInputStream, driverString)){
        driver.setFromString(driverString);
        drivers.push_back (driver);
    }

    fileInputStream.close();

	return drivers;
}
