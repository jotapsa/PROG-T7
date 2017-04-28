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

void wait_for_enter();

void ask_int(std::string string, int *number);

int opcao(int menor,int maior,int clear);

std::vector<std::string> split(const std::string &s, const char &delim);

int imprimir_menu(int menu);
#endif /* semprarrolar_h */
