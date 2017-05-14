#pragma once

//=================================
// include guard
#ifndef __SEMPRARROLAR_H
#define __SEMPRARROLAR_H

//=================================
// forward declared dependencies


//=================================
// included dependencies
#include <vector>
#include <string>

#define BEGIN 7
#define END 22
#define START_TIME BEGIN*60
#define END_TIME END*60
#define START_DAY(x) (BEGIN*60) + (24*60*x)
#define END_DAY(x) (END*60) + (24*60*x)
#define DAY 60*24

#define TOTAL_TIME 60*24*7

void wait_for_enter();

void ask_int(std::string string, int *number);

int option(int menor,int maior,bool clear);

std::vector<std::string> split(const std::string &s, const char &delim);

/*
Função responsável pela impressão do menu principal e dos respetivos sub-menus.
*/
int printMenu(int menu);

std::string hour_string(int time);

std::string time_string(int time);

std::string DayofWeek(int time);


#endif // __SEMPRARROLAR_H
