#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "line.h"
#include "semprarrolar.h"

/* We dont care if we change lineString
*/

Line::Line (unsigned int id){
	this->id = id;
}

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

bool lineWithIdExists (const std::vector<Line> &lines, const unsigned int &id){
	for (unsigned int i=0; i<lines.size(); i++){
		if (lines.at(i).getId() == id)
			return true;
	}
	return false;
}

void createLine (std::vector<Line> &lines){
	unsigned int id, id_tries=0;

	std::cout << "Introduza o ID da linha que pretende criar : ";
	std::cin >> id;

	while ((lineWithIdExists(lines, id)) && (id_tries<5)){
		std::cout << "Ja existe uma linha com esse ID, introduza outro : ";
		std::cin >> id;
		id_tries++;
	}

	if (!(id_tries<5)) {
		std::cout << "Erro! Excedeu o limite de tentativas\n";
		return;
	}
	Line line(id); //Already know we have a valid ID so we are going to create a new line

	unsigned freq;
	std::vector<std::string> stops;
	std::vector<unsigned int> timeBetweenStops;

	std::string busStop;
	unsigned int tmp;

	std::cout << "Introduza a frequencia de circulacao de autocarros : ";
	std::cin >> freq;
	line.setFreq(freq);

	std::cin.clear();
	std::cin.ignore(1000,'\n'); //clean input buffer

	std::cout << "Introduza Nomes das Paragens (Deve introduzir pelo menos 2)\n";
	while (getline (std::cin, busStop)){
		stops.push_back(busStop);
		std::cout << "Para parar de introduzir -> CTRL+Z (Windows) CTRL+D (*Nix)\n";
	}

	if ((stops.size()<2)){
		std::cout << "Uma linha deve ter mais de duas paragens!" << std::endl;
		std::cin.clear(); //Clear EOF flag
		std::cin.get();
		return;
	}

	line.setStops (stops);

	for (unsigned int i=0; i<stops.size()-1 ;i++){
		std::cout << "Tempo de viagem entre " + stops.at(i) + " e " + stops.at(i+1) + ": ";
		std::cin >> tmp;
		timeBetweenStops.push_back(tmp);
	}
	line.setTimeBetweenStops(timeBetweenStops);

	lines.push_back (line);
}
