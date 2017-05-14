//
//  semprarrolar.cpp
//  SEMPRARROLAR
//
//  Created by Bernardo Barbosa on 27/04/17.
//  Copyright © 2017 Bernardo Barbosa. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <string>
#include <limits.h> //INT_MAX

#include "semprarrolar.h"

void wait_for_enter(){
  std::cout << std::endl;
  std::cout << "Prima Enter para continuar...\n";
  system("read");
  printf("\033c");
}

void ask_int(std::string string, int *number){
  std::string invalid;
  do{
    std::cout << string;
    std::cin >> *number;
    if(std::cin.fail()){
      std::cin.clear();
      getline(std::cin,invalid);
      std::cout << "Introduza um número inteiro!\n";
      continue;
    }
    return;
  }while(1);
}

int option(int menor,int maior,bool clear){
  int op;

  do{
    ask_int("Opção: ",&op);
  }while(op < menor || op > maior);
  std::cin.ignore(INT_MAX,'\n');

  if(clear){
    printf("\033c");
  }

  if(op == maior){
    return 0;
  }

  return op;
}

std::vector<std::string> split(const std::string &s, const char &delim){
  std::vector<std::string> splitStrings;
  std::istringstream inSStream(s);

  std::string partX;

  while (getline(inSStream, partX, delim)) {
    splitStrings.push_back (partX);
  }

  return splitStrings;
}

int printMenu(int menu){
  std::fstream creditos;
  std::string s;
  printf("\033c");

  switch(menu){
    case 0:
      std::cout << "************************" << " SEMPRARROLAR " << "************************" << std::endl;
      std::cout << "1 - Gestão de Linhas\n" << "2 - Gestão de Condutores\n" << "3 - Gestão de Turnos\n" << "4 - Visualização de Informação\n" << "5 - Créditos\n" << "6 - Sair\n";
      return option(1,6, true);
    case 1:
      std::cout << "************************" << " Gestão de Linhas " << "************************" << std::endl;
      std::cout << "1 - Criar Linha\n" << "2 - Alterar Linha\n" << "3 - Remover Linha\n" << "4 - Lista de Linhas\n" << "5 - Voltar\n";
      return option(1,5, true);
    case 2:
      std::cout << "************************" << " Gestão de Condutores " << "************************" << std::endl;
      std::cout << "1 - Criar Condutor\n" << "2 - Alterar Condutor\n" << "3 - Remover Condutor\n" << "4 - Lista de Condutores\n" << "5 - Voltar\n";
      return option(1,5, true);
    case 3:
      std::cout << "************************" << " Gestão de Turnos " << "************************" << std::endl;
      std::cout << "1 - Gerar Turnos para Linha\n" << "2 - Reiniciar Turnos de Linha\n" << "3 - Reiniciar Turnos de Condutor\n" << "4 - Voltar\n";
      return option(1,4, true);
    case 4:
      std::cout << "************************" << " Visualização de Informação " << "************************" << std::endl;
      std::cout << "1 - Horários\n" << "2 - Percursos\n" << "3 - Turnos\n" << "4 - Voltar\n";
      return option(1,4, true);
    case 5:
      creditos.open("README.txt",std::ios::in);
      if(!creditos.is_open()){
        std::cout << "File not found!" << std::endl;
        return 1;
      }
      while(getline(creditos,s))
      std::cout << s << std::endl;
      creditos.close();
      break;;
    default:
      break;
  }
  return 0;
}

std::string hour_string(int time){
  int horas,minutos;
  char hora[7];
  while(time >= 60*24)
    time -= 60*24;
  horas = time/60;
  minutos = time%60;
  sprintf(hora, "%02d:%02dh", horas, minutos);
  return std::string(hora);
}

std::string time_string(int time){
  int horas,minutos;
  char hora[7];
  horas = time/60;
  minutos = time%60;
  sprintf(hora, "%02d:%02dh", horas, minutos);
  return std::string(hora);
}

std::string DayofWeek(int time){
  int i=0;
  while(time >= 60*24){
    i++;
    time -= 60*24;
  }

  switch(i){
    case 0:
      return "Segunda-feira";
    case 1:
      return "Terça-feira";
    case 2:
      return "Quarta-feira";
    case 3:
      return "Quinta-feira";
    case 4:
      return "Sexta-feira";
    case 5:
      return "Sábado";
    case 6:
      return "Domingo";
    default:
      return "";
  }
}
