//
//  semprarrolar.hpp
//  SEMPRARROLAR
//
//  Created by Bernardo Barbosa on 27/04/17.
//  Copyright © 2017 Bernardo Barbosa. All rights reserved.
//

#ifndef semprarrolar_h
#define semprarrolar_h

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <string>

#define BEGIN 7
#define END 22
#define START_TIME BEGIN*60
#define END_TIME END*60
#define START_DAY(x) (BEGIN*60) + (24*60*x)
#define END_DAY(x) (END*60) + (24*60*x)
#define DAY 60*24

void wait_for_enter();

void ask_int(std::string string, int *number);

int opcao(int menor,int maior,int clear);

std::vector<std::string> split(const std::string &s, const char &delim);

/*
 Função responsável pela impressão do menu principal e dos respetivos sub-menus.
 */
int imprimir_menu(int menu);

std::string hora_string(int time);

std::string DiadaSemana(int time);
#endif /* semprarrolar_h */
