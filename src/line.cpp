
#include "line.h"
#include <string>
#include <sstream>


std::vector<string> explode(const std::string &s, const char &c)
{
	std::string buff("");
	std::vector<std::string> v;

	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);

	return v;
}

Line::Line (std::string lineString){
}

void Line::readLine (std::string lineString){

    std::vector<std::string> split(explode(lineString,';'))
    for (int i=0; i<split.size(); i++)
    {
        std::cout << split.at(i);
    }

}
