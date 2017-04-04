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
    Line (){}; //Just create the object
    Line (unsigned int id);
    void setFromString (std::string &lineString); //Pass it by reference, so we don't have to copy anything
    //setters
    void setId (unsigned int id){this->id=id;};
    void setFreq (unsigned int freq){this->freq=freq;};
    void setStops (std::vector<std::string> stops){this->stops=stops;};
    void setTimeBetweenStops (std::vector<unsigned int> timeBetweenStops){this->timeBetweenStops=timeBetweenStops;};
    //getters
    unsigned int getId () const {return id;};

};


/*
Reads a entire file with the formated input id;freq;[stops];[timeBetweenStops] and returns a vector with Line Objects
*/
std::vector<Line> readLinesFile ();
void createLine (std::vector<Line> &lines);

#endif // __LINE_h
