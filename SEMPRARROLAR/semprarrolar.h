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

#define START 7*60
#define END 22*60
#define START_DAY(x) (7*60) + (24*60*x)
#define END_DAY(x) (22*60) + (24*60*x)

void wait_for_enter();

void ask_int(std::string string, int *number);

int opcao(int menor,int maior,int clear);

std::vector<std::string> split(const std::string &s, const char &delim);

/*
 Função responsável pela impressão do menu principal e dos respetivos sub-menus.
 */
int imprimir_menu(int menu);

void verificar_hora(int *time,int *horas,int *minutos);
#endif /* semprarrolar_h */
