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
    void setFromString (std::string &lineString);
    //setters
    void setId (unsigned int id);
    void setFreq (unsigned int freq);
    void setStops (std::vector<std::string> stops);
    void setTimeBetweenStops (std::vector<unsigned int> timeBetweenStops);
    //getters
    unsigned int getId () const;
    unsigned int getFreq () const;
    std::vector<std::string> getStops () const;
    std::vector<unsigned int> getTimeBetweenStops () const;
    //
    void addStop (unsigned int pos);
    void removeStop (unsigned int pos);

};


/*
Reads a entire file with the formated input id;freq;[stops];[timeBetweenStops] and returns a vector with Line Objects
*/
void readLinesFile (const std::string &linesFilePath, std::vector<Line> &lines);
void createLine (std::vector<Line> &lines);
unsigned int getLineIndex (const std::vector<Line> &lines);
void changeLineId (std::vector<Line> &lines, unsigned int lineIndex);
void changeLineFreq (std::vector<Line> &lines, unsigned int lineIndex);
void changeLineTimeBetweenStops (std::vector<Line> &lines, unsigned int lineIndex);;

void printLines (const std::vector<Line> &lines);

void removeLine (std::vector<Line> &lines, unsigned int lineIndex);

void storeLines (std::string filePath, const std::vector<Line> &lines);

std::string getStop (const std::vector<Line> &lines);
void stopTimeTable (const std::string &stop, const std::vector<Line> &lines);
void lineTimeTable (const Line &line);

#endif // __LINE_h

/*
bool sort_linha (Linha i,Linha j) {
    return (i.ID<j.ID);
}

void ordenar_linhas(std::vector<Linha> *Linhas){
    sort(Linhas->begin(),Linhas->end(),sort_linha);
}
*/
