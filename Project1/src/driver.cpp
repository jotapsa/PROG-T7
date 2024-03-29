#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>  //std::sort

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
  inSStream.clear();
	inSStream >> id;

	//Second element is the name
  name = splitStrings.at(1);

	//Maximum hours per shift
	inSStream.str(splitStrings.at(2));
  inSStream.clear();
	inSStream >> maxShiftHours;

	//Maximum hours per week
	inSStream.str(splitStrings.at(3));
  inSStream.clear();
	inSStream >> maxWeekHours;

  //Minimin hours between shifts
  inSStream.str(splitStrings.at(4));
  inSStream.clear();
  inSStream >> minBetweenShiftHours;
}


std::vector<Driver> readDriversFile (const std::string &driversFilePath){
  std::ifstream fileInputStream;

  std::vector<Driver> drivers;
  std::string driverString;

  fileInputStream.open(driversFilePath);

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
  unsigned int id;
  clearConsole();

  nextUnsignedInt ("ID : ", id);
  while (driverPosInVector(drivers, id)!=-1){
    nextUnsignedInt ("Ja existe um condutor com esse ID, introduza outro : ", id);
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
    std::cout << i+1 << " - " << drivers.at(i).getId() << ": " << drivers.at(i).getName()<< std::endl;
  }
  do{
    nextUnsignedInt ("Digite a sua opcao e presse ENTER: ", choice);
  }while (choice>drivers.size() || choice<1);

  return choice-1;
}

void changeDriverId (std::vector<Driver> &drivers, unsigned int driverIndex){
  unsigned int newId;

	clearConsole();

	std::cout << "ID atual : " << drivers.at(driverIndex).getId()  << std::endl;
	nextUnsignedInt("ID novo : ", newId);

	while (driverPosInVector(drivers, newId) != -1){
		std::cout << "Ja existe um condutor com esse ID.\n";
		nextUnsignedInt("ID novo : ", newId);
	}

	drivers.at(driverIndex).setId(newId);
}

void changeDriverName (Driver &driver){
  std::string newName;

	clearConsole();

	std::cout << "Nome atual : " << driver.getName()  << std::endl;
  std::cout << "Nome novo : ";
  getline (std::cin, newName);

	driver.setName(newName);
}

void changeDriverMaxShiftHours (Driver &driver){
  unsigned int newMaxShiftHours;

	clearConsole();

	std::cout << "Maximo de horas por turno atual : " << driver.getMaxShiftHours()  << std::endl;
  nextUnsignedInt("Maximo de horas por turno novo : ", newMaxShiftHours);

	driver.setMaxShiftHours(newMaxShiftHours);
}

void changeDriverMaxWeekHours (Driver &driver){
  unsigned int newMaxWeekHours;

	clearConsole();

	std::cout << "Maximo de horas por semana atual : " << driver.getMaxWeekHours()  << std::endl;
  nextUnsignedInt("Maximo de horas por semana novo : ", newMaxWeekHours);

	driver.setMaxWeekHours(newMaxWeekHours);
}

void changeDriverMinBetweenShiftHours (Driver &driver){
  unsigned int newMinBetweenShiftHours;

	clearConsole();

	std::cout << "Minimo de horas por descanso atual : " << driver.getMinBetweenShiftHours()  << std::endl;
  nextUnsignedInt("Minimo de horas por descanso novo : ", newMinBetweenShiftHours);

	driver.setMinBetweenShiftHours(newMinBetweenShiftHours);
}

void removeDriver (std::vector<Driver> &drivers, unsigned int driverIndex){
  char decision;

  clearConsole();

  std::cout << "Quer remover o condutor com ID " << drivers.at(driverIndex).getId()  << " - "<< drivers.at(driverIndex).getName() <<std::endl;
  std::cout << "Y(y) / N(n)\n";
  std::cin >> decision;

  std::cin.clear();
  std::cin.ignore(1000,'\n'); //clean input buffer

  if (decision == 'Y' || decision == 'y'){
    drivers.erase(drivers.begin() + driverIndex);
  }

}

void writeDriverToFile (std::ofstream &fileOutputStream, Driver driver){

  fileOutputStream << driver.getId () << ";";
  fileOutputStream << driver.getName () << ";";
  fileOutputStream << driver.getMaxShiftHours () << ";";
  fileOutputStream << driver.getMaxWeekHours () << ";";
  fileOutputStream << driver.getMinBetweenShiftHours () << std::endl;
}

void storeDrivers (std::string filePath, const std::vector<Driver> &drivers){
  std::ofstream fileOutputStream;

  fileOutputStream.open(filePath);
  //"../input/condutores.txt"

  if (!fileOutputStream.is_open()){
    std::cerr << "Output file opening failed.\n";
    exit(1);
  }

  for (unsigned int i=0; i<drivers.size(); i++){
    writeDriverToFile (fileOutputStream, drivers.at(i));
  }

  fileOutputStream.close();
}

bool driverComp (const Driver &i, const Driver &j) {
    return (i.getId() < j.getId());
}

void sortDrivers (std::vector<Driver> &drivers){
    sort(drivers.begin(), drivers.end(), driverComp);
}
