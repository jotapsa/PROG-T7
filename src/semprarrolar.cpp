#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "line.h"
#include "driver.h"


std::vector<std::string> split(const std::string &s, const char &delim){
	std::vector<std::string> splitStrings;
    std::istringstream inSStream(s);

    std::string partX;

    while (getline(inSStream, partX, delim)) {
        splitStrings.push_back (partX);
    }

	return  splitStrings;
}

int main (){

    std::vector<Line> lines = readLinesFile();

    std::vector<Driver> drivers = readDriversFile ();


    return 0;
}
