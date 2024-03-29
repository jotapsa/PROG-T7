//=================================
// include guard
#ifndef __LINE_H
#define __LINE_H

//=================================
// forward declared dependencies

//=================================
// included dependencies
#include <vector>
#include <string>

//=================================


class Line {
private:
    unsigned int id;
    unsigned int freq;
    std::vector<std::string> lineStops;
    std::vector<unsigned int> timeBetweenStops;
public:
    Line (){}; //Just create the object
    Line (unsigned int id);
    //setters
    void setFromString (std::string &lineString);
    void setId (unsigned int id);
    void setFreq (unsigned int freq);
    void setStops (std::vector<std::string> stops);
    void setTimeBetweenStops (std::vector<unsigned int> timeBetweenStops);
    //getters
    unsigned int getId () const;
    unsigned int getFreq () const;
    std::vector<std::string> getStops () const;
    std::vector<unsigned int> getTimeBetweenStops () const;
    //methods
    void addStop (unsigned int pos);
    void removeStop (unsigned int pos);
    void changeTimeBetweenStops (unsigned int pos);

};


/*
Reads a entire file with the formated input id;freq;[stops];[timeBetweenStops] and returns a vector with Line Objects
*/
std::vector<Line> readLinesFile (const std::string &linesFilePath);
void createLine (std::vector<Line> &lines);
unsigned int getLineIndex (const std::vector<Line> &lines);
void changeLineId (std::vector<Line> &lines, unsigned int lineIndex);
void changeLineFreq (Line &line);
void changeLineTimeBetweenStops (std::vector<Line> &lines, unsigned int lineIndex);;

void printLines (const std::vector<Line> &lines);

void removeLine (std::vector<Line> &lines, unsigned int lineIndex);

void storeLines (std::string filePath, const std::vector<Line> &lines);

std::string getStop (const std::vector<Line> &lines);
void stopTimeTable (const std::string &stop, const std::vector<Line> &lines);
void lineTimeTable (const Line &line);
void routeTimeTable (const std::vector<Line> &lines);

void sortLines (std::vector<Line> &lines);

#endif // __LINE_H
