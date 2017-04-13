//=================================
// include guard
#ifndef __STOPS_H
#define __STOPS_H

//=================================
// included dependencies
#include <vector>
#include <string>


class Stop{
private:
  std::string name;
  std::vector<unsigned int> belongsTo; //vector with the id of the lines it belongs to
public:
  Stop (){}; //Just create the object
  std::string getNAme(){return name};
};

#endif // __MENU_H
