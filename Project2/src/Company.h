#pragma once

//=================================
// include guard
#ifndef __COMPANY_H
#define __COMPANY_H

//=================================
// forward declared dependencies
#include "Driver.h"
#include "Line.h"

//=================================
// included dependencies
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Company{
 private:
  string nome;
  vector<Driver> drivers;
  vector<Line> lines;
    string fichCondutores,fichLinhas;
 public:
    Company(string nome, string fichCondutores, string fichLinhas);

  // get methods
  string getNome() const;
    vector<Line> getLines() const;
    vector<Driver> getDrivers() const;

  // set methods

  // other methods
  void distribuiServico(); // funcao que implementa a afectacao de servico
    static bool sort_linha (Line i,Line j);
    void ordenarLinhas();
    static bool sort_condutor (Driver i,Driver j);
    void ordenarCondutores();
    void imprimirLinhas();
    void imprimirCondutores();
    bool checkForLine(unsigned int ID);
    int novaLinha(bool *changed);
    int displayLinhas(std::string Title);
    int alterarLinha(bool *changed);
    int removerLinha(bool *changed);
    bool verificarCondutor(int ID);
    int novoCondutor(bool *changed);
    int displayCondutores();
    int alterarCondutor(bool *changed);
    int removerCondutor(bool *changed);
    int imprimirHorarios();
    static bool sort_paragem (std::string i,std::string j);
    void ordenarParagens();
    int HorarioParagem();
    int PercursoParagens();
    void atualizarLinhas();
    void atualizarCondutores();
    void gerarTurnos();
    void reiniciarTurnos();
    void imprimirTurnoLinha();
    void imprimirTurnoCondutor();
};

#endif
