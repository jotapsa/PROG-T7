#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "driver.h"
#include "semprarrolar.h"

Driver::Driver (unsigned int id){
  this->id = id;
}

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

    clearConsole();

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
    getchar();
}

int driverPosInVector (const std::vector<Driver> &drivers, const unsigned int &id){
	for (unsigned int i=0; i<drivers.size(); i++){
		if (drivers.at(i).getId() == id)
			return i;
	}
	return -1; //-1 if we didn't find anything
}


void createDriver (std::vector<Driver> &drivers){
  unsigned int id, id_tries=0;
  clearConsole();

  nextUnsignedInt ("ID : ", id);

  while ((driverPosInVector(drivers, id)!=-1) && (id_tries<5)){
    nextUnsignedInt ("Ja existe um condutor com esse ID, introduza outro : ", id);
    id_tries++;
  }

  if (!(id_tries<5)) {
    std::cout << "Erro! Excedeu o limite de tentativas\n";
    return;
  }

  Driver driver(id);
  std::string name;
  unsigned int maxShiftHours, maxWeekHours, minBetweenShiftHours;

  std::cout << "Nome : ";
  getline (std::cin, name);
  driver.setName (name);

  nextUnsignedInt ("Maximo de horas por turno : ", maxShiftHours);
  driver.setMaxShiftHours(maxShiftHours);

  nextUnsignedInt ("Maximo de horas por semana : ", maxWeekHours);
  driver.setMaxWeekHours (maxWeekHours);

  nextUnsignedInt ("Minimo de horas por descanso : ", minBetweenShiftHours);
  driver.setMinBetweenShiftHours (minBetweenShiftHours);

  drivers.push_back (driver);
}


unsigned int getDriverIndex(const std::vector<Driver> &drivers){
  unsigned int choice;

  clearConsole();
  std::cout << "*******************************\n";

  for (unsigned int i=0; i<drivers.size(); i++){
    std::cout << i+1 << " - " << drivers.at(i).getId() << std::endl;
  }

  nextUnsignedInt ("Opcao : ", choice);
  return choice-1;
}
