//=================================
// include guard
#ifndef __TIME_H
#define __TIME_H

//=================================
// forward declared dependencies

//=================================
// included dependencies
#include <string>

//=================================


class Time {
private:
  unsigned int hour;
  unsigned int minutes;
public:
  //constructors
  Time ();
  Time (unsigned int hour, unsigned int minutes);
  //getters
  unsigned int getHour() const;
  unsigned int getMinutes() const;
  //setters
  void setHour (unsigned int hour);
  void setMinutes (unsigned int minutes);
  void setTime (unsigned int hour, unsigned int minutes);
  //methods
  void addMinutes (unsigned int minutes);
  bool before (unsigned int hour, unsigned int minutes);
  std::string toString ();
};

#endif // __TIME_H
