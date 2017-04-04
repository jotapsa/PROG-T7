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
    std::vector<std::string> stops;
    std::vector<unsigned int> timeBetweenStops;
public:
    void setFromString (std::string &lineString); //Pass it by reference, so we don't have to copy anything

};


/*
Reads a entire file with the formated input id;freq;[stops];[timeBetweenStops] and returns a vector with Line Objects
*/
std::vector<Line> readLinesFile ();

#endif // __LINE_h
