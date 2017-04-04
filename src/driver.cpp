#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>

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

int sizeOfBiggestName (const std::vector<Driver> &drivers){
    unsigned int max = 0;
    for (unsigned int i=0; i<drivers.size();i++){
        if (drivers.at(i).getName().size() > max){
            max = drivers.at(i).getName().size();
        }
    }
    return max;
}


void printDrivers (const std::vector<Driver> &drivers){
    static unsigned int nDrivers = drivers.size(); // Will be used to format our table;
    static unsigned int maxLengthName = sizeOfBiggestName (drivers);
    //Check to see if our drivers list has been updated
    if (drivers.size () !=  nDrivers){
        maxLengthName = sizeOfBiggestName (drivers);
    }
    std::cout.width(6);
    std::cout << std::left << "ID";
    std::cout.width(maxLengthName);
    std::cout << std::left << "Name" << std::endl;
    for (unsigned int i= 0; i<drivers.size(); i++){
        std::cout.width(6);
        std::cout << std::left << drivers.at(i).getId();
        std::cout.width(maxLengthName);
        std::cout << std::left << drivers.at(i).getName() << std::endl;
    }
    std::cout << "\n\n\n\n";
}
