#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Line.h"
#include "Driver.h"
#include "semprarrolar.h"

using namespace std;

class Empresa{
 private:
  string nome;
  vector<Driver> drivers;
  vector<Line> lines;
    string fichCondutores,fichLinhas;
 public:
    Empresa(string nome, string fichCondutores, string fichLinhas);
  // metodos get
  string getNome() const;
    vector<Line> getLines() const;
    vector<Driver> getDrivers() const;
  // metodos set
  // outros metodos
  void distribuiServico(); // funcao que implementa a afectacao de servico
    static bool sort_linha (Line i,Line j);
    void ordenarLinhas();
    static bool sort_condutor (Driver i,Driver j);
    void ordenarCondutores();
    void imprimirLinhas();
    void imprimirCondutores();
    bool verificarLinha(int ID);
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
};

