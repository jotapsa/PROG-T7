#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "line.h"
#include "semprarrolar.h"

/* We dont care if we change lineString
*/

void Line::setFromString (std::string &lineString){
    std::vector<std::string> splitStrings(split(lineString,';'));

	std::istringstream inSStream;

	std::string busStop;
	unsigned int stopTime;

	//Check the size
	if (splitStrings.size() != 4){
		//error
	}

    //Already know the first element is the id
	inSStream.str(splitStrings.at(0));
	inSStream >> id;

	//Second element is the frequency
	inSStream.str(splitStrings.at(1));
	inSStream >> freq;

	//Stop sequence
	inSStream.str(splitStrings.at(2));
	for (unsigned int i=0; i<splitStrings.at(2).size(); i++){
		inSStream >> busStop;
		stops.push_back (busStop);
	}

	//busStop frequency
	inSStream.str(splitStrings.at(3));
	for (unsigned int i=0; i<splitStrings.at(2).size(); i++){
		inSStream >> stopTime;
		timeBetweenStops.push_back (stopTime);
	}
}


std::vector<Line> readLinesFile (){
	std::ifstream fileInputStream;

    std::vector<Line> lines;
    std::string lineString;

    fileInputStream.open("../input/linhas.txt"); //for linux
    //fileInputStream.open("..//input//linhas.txt"); //for Windows (i think)

    if (!fileInputStream.is_open()){
        std::cerr << "Input file opening failed.\n";
        exit(1);
    }

    Line line;
    while (getline(fileInputStream, lineString)){
        line.setFromString(lineString);
        lines.push_back (line);
    }

    fileInputStream.close();

	return lines;
}
