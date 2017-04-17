#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "line.h"
#include "time.h"
#include "semprarrolar.h"


Line::Line (unsigned int id){
	this->id = id;
}

void Line::setFromString (std::string &lineString){
  std::vector<std::string> splitStrings(split(lineString,';'));
	std::vector<std::string> busStops(split(splitStrings.at(2),','));
	std::vector<std::string> timeStops(split(splitStrings.at(3),','));

	//Remover espacos no inicio
	for (unsigned int i=0; i<busStops.size(); i++){
		if (busStops.at(i).at(0) == ' '){
			busStops.at(i).erase (busStops.at(i).begin());
		}
	}
	for (unsigned int i=0; i<timeStops.size(); i++){
		if (timeStops.at(i).at(0) == ' '){
			timeStops.at(i).erase (timeStops.at(i).begin());
		}
	}

	std::istringstream inSStream;
	unsigned int stopTime;

	//Check the size
	if (splitStrings.size() != 4){
		//error
	}

    //Already know the first element is the id
	inSStream.str(splitStrings.at(0));
	inSStream.clear();
	inSStream >> id;

	//Second element is the frequency
	inSStream.str(splitStrings.at(1));
	inSStream.clear();
	inSStream >> freq;

	//Stop sequence
	lineStops.clear ();
	for (unsigned int i=0; i<busStops.size(); i++){
		lineStops.push_back(busStops.at(i));
	}

	//busStop frequency
	timeBetweenStops.clear();
	for (unsigned int i=0; i<timeStops.size(); i++){
		inSStream.str(timeStops.at(i));
		inSStream.clear();
		inSStream >> stopTime;
		timeBetweenStops.push_back (stopTime);
	}
}

void Line::setId (unsigned int id){
	this->id=id;
}

void Line::setFreq (unsigned int freq){
	this->freq=freq;
}

void Line::setStops (std::vector<std::string> stops){
	this->lineStops=stops;
}

void Line::setTimeBetweenStops (std::vector<unsigned int> timeBetweenStops){
	this->timeBetweenStops=timeBetweenStops;
}

unsigned int Line::getId () const {
	return id;
}

unsigned int Line::getFreq () const{
	return freq;
}

std::vector<std::string>  Line::getStops () const{
	return lineStops;
}

std::vector<unsigned int> Line::getTimeBetweenStops () const{
	return timeBetweenStops;
}

void Line::addStop (unsigned int pos){
	std::string stopName;
	unsigned int timeStop;

	std::cout << "Nome da nova paragem: ";
	getline(std::cin, stopName);

	if (pos != lineStops.size()){
		std::cout << "Tempo de viagem entre " << stopName << " e " << lineStops.at(pos);
		nextUnsignedInt (" : ", timeStop);
		timeBetweenStops.insert(timeBetweenStops.begin()+pos, timeStop);
	}

	if (pos != 0){
		std::cout << "Tempo de viagem entre " << lineStops.at(pos-1) << " e " << stopName;
		nextUnsignedInt (" : ", timeStop);
		timeBetweenStops.insert(timeBetweenStops.begin()+pos-1, timeStop);
	}

	if (pos!=0 && pos != lineStops.size()){
		timeBetweenStops.erase(timeBetweenStops.begin()+pos);
	}

	lineStops.insert(lineStops.begin()+pos, stopName);
}

void Line::removeStop (unsigned int pos){

	if (pos == 0 || pos ==(lineStops.size()-1)){
		timeBetweenStops.erase(timeBetweenStops.begin()+pos-1);
	}
	else{
		timeBetweenStops.at(pos-1) += timeBetweenStops.at(pos);
		timeBetweenStops.erase(timeBetweenStops.begin()+pos);
	}
	lineStops.erase(lineStops.begin()+(pos));
}

void readLinesFile (const std::string &linesFilePath, std::vector<Line> &lines){
	std::ifstream fileInputStream;
	std::string lineString;

	fileInputStream.open(linesFilePath);

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
}

int linePosInVector (const std::vector<Line> &lines, const unsigned int &id){
	for (unsigned int i=0; i<lines.size(); i++){
		if (lines.at(i).getId() == id)
			return i;
	}
	return -1; //-1 if we didn't find anything
}

void createLine (std::vector<Line> &lines){
	unsigned int id, id_tries=0, n;
	clearConsole();

	nextUnsignedInt ("ID : ", id);

	while ((linePosInVector(lines, id)!=-1) && (id_tries<5)){
		nextUnsignedInt ("Ja existe uma linha com esse ID, introduza outro : ", id);
		id_tries++;
	}

	if (!(id_tries<5)) {
		std::cout << "Erro! Excedeu o limite de tentativas\n";
		return;
	}
	Line line(id); //Already know we have a valid ID so we are going to create a new line

	unsigned int freq;
	std::vector<std::string> stops;
	std::vector<unsigned int> timeBetweenStops;

	std::string busStop;
	unsigned int tmp;

	nextUnsignedInt ("Frequencia de circulacao: ", freq);
	line.setFreq(freq);

	nextUnsignedInt ("Nº Paragens: ", n);

	if (n<2){
		std::cout << "Uma linha deve ter pelo menos duas paragens!" << std::endl;
		std::cin.get();
		return;
	}

	for (unsigned int i=0; i<n; i++){
		std::cout << stops.size()+1 << "ª Paragem: ";
		getline (std::cin, busStop);
		stops.push_back(busStop);
	}

	std::cin.clear(); //Clear EOF flag

	line.setStops (stops);

	for (unsigned int i=0; i<stops.size()-1 ;i++){
		nextUnsignedInt ("Tempo de viagem entre " + stops.at(i) + " e " + stops.at(i+1) + ": ", tmp);
		timeBetweenStops.push_back(tmp);
	}
	line.setTimeBetweenStops(timeBetweenStops);

	lines.push_back (line);
}


unsigned int getLineIndex (const std::vector<Line> &lines){
	unsigned int choice;

	clearConsole();
	std::cout << "*******************************\n";

	for (unsigned int i=0; i<lines.size(); i++){
		std::cout << i+1 << " - " << lines.at(i).getId() << std::endl;
	}

	nextUnsignedInt ("Opcao : ", choice);

	return choice-1;
}

void changeLineId (std::vector<Line> &lines, unsigned int lineIndex){
	unsigned int newId;

	clearConsole();

	std::cout << "ID atual : " << lines.at(lineIndex).getId()  << std::endl;
	nextUnsignedInt("ID novo : ", newId);

	while (linePosInVector(lines, newId) != -1){
		std::cout << "Ja existe uma linha com esse ID.\n";
		nextUnsignedInt("ID novo : ", newId);
	}

	lines.at(lineIndex).setId(newId);
}

void changeLineFreq (Line &line){
	unsigned int newFreq;

	clearConsole();

	std::cout << "Frequencia atual : " << line.getFreq()  << std::endl;
	nextUnsignedInt("Frequencia nova : ", newFreq);

	line.setFreq(newFreq);
}

void changeLineTimeBetweenStops (std::vector<Line> &lines, unsigned int lineIndex){

}


void printLines (const std::vector<Line> &lines){
	std::vector<std::string> stops;
	std::vector<unsigned int> timeBetweenStops;
	clearConsole();

	std::cout << "*******************************\n\n";
	for (unsigned int i=0; i<lines.size(); i++){
		std::cout << "Linha " << lines.at(i).getId() << std::endl;
		std::cout << "Frequencia : " << lines.at(i).getFreq() << std::endl;
		stops = lines.at(i).getStops();
		for (unsigned int j=0; j<stops.size(); j++){
			if (j!=0){
				std::cout << " - ";
			}
			std::cout << stops.at(j);
		}
		std::cout << std::endl;

		timeBetweenStops = lines.at(i).getTimeBetweenStops();
		for (unsigned int j=0; j<timeBetweenStops.size(); j++){
			if (j!=0){
				std::cout << " - ";
			}
			std::cout  << timeBetweenStops.at(j);
		}
		std::cout << "\n\n";
	}

	getchar();
}

void removeLine (std::vector<Line> &lines, unsigned int lineIndex){
  char decision;

  clearConsole();

  std::cout << "Quer remover a linha com ID " << lines.at(lineIndex).getId() <<std::endl;
  std::cout << "Y(y) / N(n)\n";
  std::cin >> decision;

  std::cin.clear();
  std::cin.ignore(1000,'\n'); //clean input buffer

  if (decision == 'Y' || decision == 'y'){
    lines.erase(lines.begin() + lineIndex);
  }

}


void writeLineToFile (std::ofstream &fileOutputStream, Line line){
	std::vector<std::string> stops = line.getStops();
	std::vector<unsigned int> timeBetweenStops = line.getTimeBetweenStops();

  fileOutputStream << line.getId () << ";";
  fileOutputStream << line.getFreq () << ";";
	for(unsigned int i=0; i<stops.size(); i++){
		if(i!=0){
			fileOutputStream << ", ";
		}
		fileOutputStream << stops.at(i);
	}
	fileOutputStream << ";";

	for(unsigned int i=0; i<timeBetweenStops.size(); i++){
		if(i!=0){
			fileOutputStream << ",";
		}
		fileOutputStream << " " << timeBetweenStops.at(i);
	}
	fileOutputStream << std::endl;
}

void storeLines (std::string filePath, const std::vector<Line> &lines){
  std::ofstream fileOutputStream;

  fileOutputStream.open(filePath);

  if (!fileOutputStream.is_open()){
    std::cerr << "Output file opening failed.\n";
    exit(1);
  }

  for (unsigned int i=0; i<lines.size(); i++){
    writeLineToFile (fileOutputStream, lines.at(i));
  }

  fileOutputStream.close();
}

int stopInLineStopsIndex (const std::string &stop, const std::vector<std::string> &stops){
	for (unsigned int i=0; i<stops.size(); i++){
		if (stops.at(i).compare(stop) == 0){
			return i;
		}
	}
	return -1;
}

std::string getStop (const std::vector<Line> &lines){
	std::vector<std::string> stops; //No repetitions
	std::vector<std::string> lineStops;
	int choice;

	for (unsigned int i=0; i<lines.size(); i++){
		lineStops = lines.at(i).getStops();
		for (unsigned int j=0; j<lineStops.size(); j++){
			if (stopInLineStopsIndex(lineStops.at(j), stops) == -1 ){
				stops.push_back(lineStops.at(j));
			}
		}
	}

	clearConsole ();

	for (unsigned int i=0; i<stops.size(); i++){
		std::cout << i+1 << " - " << stops.at(i) << std::endl;
	}
	nextInt ("Escolha uma paragem e presse ENTER: ", choice);

	return stops.at(choice-1);
}

void stopTimeTable (const std::string &stop, const std::vector<Line> &lines){
	int index;
	Time busTime;
	unsigned int timeGap=0;

	std::vector<std::string> lineStops;
	std::vector<unsigned int> timeBetweenStops;

	clearConsole();

	for (unsigned int i=0; i<lines.size(); i++){
		lineStops = lines.at(i).getStops();
		timeBetweenStops = lines.at(i).getTimeBetweenStops();

		if ((index = stopInLineStopsIndex(stop, lineStops)) != -1){
			busTime.setTime (STARTHOUR, STARTMINUTES);
			timeGap=0;

			for (int j=0; j<index; j++){
				timeGap+=timeBetweenStops.at(j);
			}

			busTime.addMinutes (timeGap);

			std::cout << lines.at(i).getId() << std::endl;
			while (busTime.before (ENDHOUR, ENDMINUTES)){
				std::cout << busTime.toString() <<std::endl;
				busTime.addMinutes (lines.at(i).getFreq());
			}
		}
	}

	getchar();
}

void lineTimeTable (const Line &line){
	Time departTime(STARTHOUR, STARTMINUTES), busTime;

	std::vector<std::string> lineStops = line.getStops();
	std::vector<unsigned int> timeBetweenStops = line.getTimeBetweenStops();

	clearConsole();

	for (unsigned int i=0; i<lineStops.size(); i++){
		if (i!=0){
			std::cout << " - ";
		}
		std::cout << lineStops.at(i);
	}
	std::cout << std::endl;

	while (departTime.before(ENDHOUR, ENDMINUTES)){ //while still departing bus
		busTime.setTime(departTime.getHour(), departTime.getMinutes());

		for (unsigned int i=0; i<lineStops.size(); i++){ //for every stop
			if (i!=0){
				std::cout << " - ";
				busTime.addMinutes (timeBetweenStops.at(i-1));
			}

			std::cout << busTime.toString();
		}
		std::cout << std::endl;
		departTime.addMinutes(line.getFreq());
	}

	getchar ();

}
