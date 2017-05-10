#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstring>
#include <numeric>
#include <iomanip>
#include "semprarrolar.h"

using namespace std;

class Line{
 private:
  unsigned int id;
  unsigned int freq;
  vector<string> busStopList;
  vector<int> timesList;
 public:
  Line(string textLine);
  Line();
  // metodos get
  unsigned int getId() const;
    unsigned int getFreq() const;
  vector<string> getBusStops() const;
  vector<int> getTimings() const;
    int getIndexParagem(std::string paragem);
  // set methods
    void setId(unsigned int ID);
    void setFreq(unsigned int Freq);
  // other methods
    void addStop (std::string paragem,unsigned int pos);
    void addStop (std::string paragem);
    void addTime (int time);
    bool verificarParagem(std::string paragem);
    int TempoParagens(int origem,int destino,int sentido);
    void alinharParagem(int origem,int paragem);
    void imprimirViagem(int origem,int destino,int sentido);
    void HorarioLinha();
    int Alterar(bool *changed);
    int AlterarParagem();
    int AlterarTempos();
};
