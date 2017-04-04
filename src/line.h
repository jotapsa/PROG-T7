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
    std::vector<int> timeBetweenStops;
public:
    Line(std::string lineString);
    void readLine (std::string lineString);

};

#endif // __LINE_h
