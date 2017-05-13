/*#include <iostream>
#include <map>
#include <fstream>
#include <cstring>
#include <numeric>
#include <iomanip>
*/
#include <sstream>
#include <algorithm>    // std::find
#include <numeric>      // std::accumulate
#include <iomanip>  //setw

#include "semprarrolar.h"
#include "Line.h"


Line::Line(string textLine){
    std::vector<std::string> splitStrings(split(textLine,';'));
    std::vector<std::string> busStops(split(splitStrings.at(2),','));
    std::vector<std::string> timeStops(split(splitStrings.at(3),','));

    //Remover espacos no inicio
    for (unsigned int i=0; i<busStops.size(); i++){
        if (busStops.at(i).at(0) == ' '){
            busStops.at(i).erase (busStops.at(i).begin());
        }
    }
    for (unsigned int i=0; i<timeStops.size(); i++){
        if (timeStops.at(i).at(0) == ' '){
            timeStops.at(i).erase (timeStops.at(i).begin());
        }
    }

    std::istringstream inSStream;
    unsigned int stopTime;

    //Check the size
    if (splitStrings.size() != 4){
        return;
    }

    //Already know the first element is the id
    inSStream.str(splitStrings.at(0));
    inSStream.clear();
    inSStream >> id;

    //Second element is the frequency
    inSStream.str(splitStrings.at(1));
    inSStream.clear();
    inSStream >> freq;

    //Stop sequence
    busStopList.clear ();
    for (unsigned int i=0; i<busStops.size(); i++){
        busStopList.push_back(busStops.at(i));
    }

    //busStop frequency
    timesList.clear();
    for (unsigned int i=0; i<timeStops.size(); i++){
        inSStream.str(timeStops.at(i));
        inSStream.clear();
        inSStream >> stopTime;
        timesList.push_back (stopTime);
    }

    createShifts();
}

Line::Line(){}

////////////////
// get methods
////////////////

unsigned int Line::getId() const{
  return id;
}

unsigned int Line::getFreq() const{
    return freq;
}

vector<string> Line::getBusStops() const{
  return busStopList;
}

vector<int> Line::getTimings() const{
  return timesList;
}

int Line::getIndexParagem(std::string stop) const{
    return (int) std::distance(busStopList.begin(), std::find(busStopList.begin(), busStopList.end(), stop));
}

vector<Bus> Line::getBuses() const{
    return buses;
}

int Line::getShiftTime(){
    return shiftTime;
}

////////////////
// set methods
////////////////

void Line::setId(unsigned int ID){
    this->id = ID;
}

void Line::setFreq(unsigned int Freq){
    this->freq = Freq;
}

////////////////
// other methods
////////////////

void Line::createShifts(){
  int i,day,viagens_dia,bus,n;

  //Reset Shifts vector
  shifts.clear();

  //Shift time of Line
  shiftTime = tripTime(0, busStopList.size(), 1)*2;

  //Shifts With Only Times and LineId
  for(day=0;day<7;day++){
      for(i=START_DAY(day);i< END_DAY(day);i+=freq){
          shifts.push_back(Shift(id,i,i + shiftTime));
      }
  }

  viagens_dia = ((END - BEGIN)*60) / freq;
  n = (int) ((double) shiftTime / freq + 1.0);

  //minimum buses
  for(i=1;i<=n;i++)
      buses.push_back(Bus(i,id));

  for(day=0;day<7;day++){
      bus=1;
      for(i=0;i<viagens_dia;i++){
          shifts.at(day*viagens_dia + i).setBusOrderNumber(bus);
          buses.at(bus-1).getSchedule().push_back(shifts.at(day*viagens_dia + i));
          bus++;
          if(bus>=n)
              bus = 1;
      }
  }
}

void Line::addStop (std::string stop,unsigned int pos){
    int timeStop;

    if (pos != 0){
        ask_int("Tempo de viagem entre " + busStopList.at(pos-1) + " e " + stop + " (minutos): ",&timeStop);
        timesList.insert(timesList.begin()+pos-1, timeStop);
    }

    if (pos != busStopList.size()){
        ask_int("Tempo de viagem entre " + stop + " e " + busStopList.at(pos) + " (minutos): ",&timeStop);
        timesList.insert(timesList.begin()+pos, timeStop);
    }

    if (pos!=0 && pos != busStopList.size()){
        timesList.erase(timesList.begin()+pos+1);
    }

    busStopList.insert(busStopList.begin()+pos, stop);
}

void Line::addStop (std::string stop){
    busStopList.push_back(stop);
}

void Line::addTime (int time){
    timesList.push_back(time);
}

bool Line::checkStop(std::string stop){
    return (std::find(busStopList.begin(),busStopList.end(),stop) != busStopList.end()) ? true : false;
}


unsigned int Line::tripTime(unsigned int origin,unsigned int destiny,unsigned int way){
  //Wich way are we going ?
  if(way==1){
    return std::accumulate(timesList.begin() + origin,timesList.begin() + destiny,0);
  }
  else{
    return std::accumulate(timesList.begin() + destiny,timesList.begin() + origin,0);
  }
}


void Line::alignStop(int origem,int stop){
    int espaco;
    if(busStopList.at(stop).length() < 6)
        espaco = 6;
    else
        espaco = (int)busStopList.at(stop).length();

    if(stop == origem)
        std::cout.width(espaco);
    else
        std::cout.width(espaco + 5);
}



void Line::printTrip(unsigned int origem,unsigned int destino, int sentido){
    int time, hora_stop, viagem_completa, hora_saida;
    std::string hora;

    for(unsigned int s=origem;s!=destino+sentido;s+=sentido){
        alignStop(origem,s);
        std::cout << busStopList.at(s);
    }
    std::cout << std::endl;

    viagem_completa = tripTime(0, (int)busStopList.size()-1, 1);

    if(sentido==1)
        time = START_TIME;
    else
        time = START_TIME + viagem_completa;

    while(1){
        if(sentido==1)
            hora_stop = time + tripTime(0, origem, 1);
        else
            hora_stop = time + tripTime(origem, (int)busStopList.size()-1, 1);
        hora = hour_string(hora_stop);
        alignStop(origem,origem);
        std::cout << hora;
        for(unsigned int j=origem;j!=destino;j+=sentido){
            if( (j==timesList.size() && sentido==1) || (j==0 && sentido==-1) )
                continue;
            if(sentido==1)
                hora_stop += timesList.at(j);
            else
                hora_stop += timesList.at(j+sentido);
            hora = hour_string(hora_stop);
            alignStop(origem,j+sentido);
            std::cout << hora;
        }
        std::cout << std::endl;
        time += freq;
        if(sentido==1)
            hora_saida = time;
        else
            hora_saida = time - viagem_completa;
        if(hora_saida >= END_TIME)
            break;
    }
}



void Line::lineSchedule(){

    //SENTIDO FIRST -> LAST
    std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
    std::cout << std::endl;
    std::cout << std::setw(20) << "Sentido " << busStopList.at(0) << " -> " << busStopList.at(busStopList.size()-1) << std::endl;
    std::cout << std::endl;

    printTrip(0,(int)busStopList.size()-1,1);
    std::cout << std::endl;

    //SENTIDO LAST -> FIRST
    std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
    std::cout << std::endl;
    std::cout << std::setw(20) << "Sentido " << busStopList.at(busStopList.size()-1) << " -> " << busStopList.at(0) << std::endl;
    std::cout << std::endl;

    printTrip((int)busStopList.size()-1,0,-1);
    wait_for_enter();
}

int Line::change(bool *changed,vector<Driver> *drivers){
    int op,aux,mod = 1;
    do{
        std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
        std::cout << "1 - ID\n" << "2 - Frequência\n" << "3 - Paragens\n" << "4 - Tempo entre Paragens\n" << "5 - Voltar\n";

        op = option(1,5, true);
        if(!op)
            break;

        switch(op){
            case 1:
                do{
                    do{
                        std::cout << "ID atual -> " << id << std::endl;
                        ask_int("ID novo -> ",&aux);
                    }while(aux <=0);
//                    if(!verificar_linha(aux, Linhas)){
//                        linha->ID = aux;
//                        break;
//                    }
//                    else
//                        std::cout << "Linha " << aux << " já existe!" << std::endl;
                    id = aux;
                    mod = 0;
                    break;
                }while(1);
                break;
            case 2:
                do{
                    do{
                        std::cout << "Frequência atual -> " << freq << std::endl;
                        ask_int("Frequência nova -> ",&aux);
                    }while(aux <=0);
                    if(aux > 0)
                        freq = aux;
                    mod = 0;
                    break;
                }while(1);
                break;
            case 3:
                mod = changeStops();
                break;
            case 4:
                mod = changeTimes();
                break;
            default:
                break;
        }
        if(!mod){
            std::cout << "Linha " << id << " alterada com sucesso!" << std::endl;
            *changed = true;
            //Reconstruct schedules
            resetWeekShifts(drivers,0);
            createShifts();
            wait_for_enter();
        }
    }while(op);
    return 0;
}

int Line::changeStops(){
    unsigned int pos;
    int i=1,op=0,stop;
    std::string nome;

    do{
        printf("\033c");
        i=1;
        std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
        std::cout << "1 - Adicionar Paragem\n" << "2 - Mudar Nome de Paragem\n" << "3 - Remover Paragem\n" << "4 - Voltar\n";
        op = option(1, 4, true);
        if(!op)
            return 1;

        std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
        switch(op){
            case 1:
                std::cout << i << " - " << "Início de Linha" << std::endl;
                i++;
                for(unsigned int j=0;j<busStopList.size()-1;j++){
                    std::cout << i << " - Entre " << busStopList.at(j) << " e " << busStopList.at(j+1) << std::endl;
                    i++;
                }
                std::cout << i << " - " << "Fim de Linha" << std::endl;
                i++;

                std::cout << i << " - " << "Voltar" << std::endl;
                stop = option(1, i, false);
                if(!stop)
                    continue;

                do{
                    std::cout << "Nome da Paragem: ";
                    getline(std::cin, nome);
                }while(nome.length() <= 0 || checkStop(nome));
                addStop(nome, stop-1);

                return 0;
            case 2:
                for(std::string s : busStopList){
                    std::cout << i << " - " << s << std::endl;
                    i++;
                }
                std::cout << i << " - " << "Voltar" << std::endl;
                stop = option(1,i, false);
                if(!stop)
                    continue;

                do{
                    std::cout << std::endl << "Nome de Paragem atual -> " << busStopList.at(stop-1) << std::endl;
                    std::cout << "Nome de Paragem novo -> ";
                    getline(std::cin, nome);
                }while(nome.length() <= 0 || checkStop(nome));
                busStopList.at(stop-1) = nome;
                return 0;
            case 3:
                if(busStopList.size() <= 2){
                    std::cout << "Uma linha não pode ter menos que duas paragens!" << std::endl;
                    wait_for_enter();
                    continue;
                }

                for(std::string s : busStopList){
                    std::cout << i << " - " << s << std::endl;
                    i++;
                }
                std::cout << i << " - " << "Voltar" << std::endl;
                stop = option(1,i, false);
                if(!stop)
                    continue;

                pos = stop - 1;
                if (pos == 0 || pos ==(busStopList.size()-1)){
                    timesList.erase(timesList.begin()+pos-1);
                }
                else{
                    timesList.at(pos-1) += timesList.at(pos);
                    timesList.erase(timesList.begin()+pos);
                }
                busStopList.erase(busStopList.begin()+(pos));
                return 0;
            default:
                break;
        }
    }while(op);
    return 0;
}

int Line::changeTimes(){
    int i=1,op=0,tempo;
    std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
    for(unsigned int j=0;j<busStopList.size()-1;j++){
        std::cout << i << " - Entre " << busStopList.at(j) << " e " << busStopList.at(j+1) << " (" << timesList.at(j) << " minutos)"<< std::endl;
        i++;
    }
    std::cout << i << " - " << "Voltar" << std::endl;
    op = option(1,i, false);
    if(!op){
        printf("\033c");
        return 1;
    }

    do{
        ask_int("Tempo entre " + busStopList.at(op-1) + " e " + busStopList.at(op) + ": ", &tempo);
    }while(tempo <= 0);
    timesList.at(op-1) = tempo;
    return 0;
}

void Line::generateWeekShifts(vector<Driver> *drivers){
  Driver *driver;
  unsigned int workHours;
  Shift *shift;
  int restStart, restEnd;
  vector<bool> workTime;
  bool flag = true;

  for (unsigned int i=0; i<drivers->size(); i++){
    driver = &drivers->at(i);
    workHours = driver->getWorkHours();
    //Can he work this shift?
    if (driver->getMaxHours() >= shiftTime){
      //If he has time
      for (unsigned int j=0; (((workHours+shiftTime)<=driver->getMaxWeekWorkingTime()) && (j<shifts.size())); j++){
        shift = &shifts.at(j);

        if (!shift->getDriverId()){
          restStart = shift->getStartTime()-driver->getMinRestTime();
          if (restStart<0){
            restStart=0;
          }

          restEnd = shift->getEndTime()+driver->getMinRestTime();
          if (restEnd>(TOTAL_TIME)){
            restEnd = TOTAL_TIME;
          }
          workTime = driver->getWorkTime();

          //Can we fit a shift in his schedule?
          flag = true;
          for (unsigned int k=restStart; k<restEnd; k++){
            if (workTime.at(k)){
              flag = false;
              break; //not necessary but this way we dont need to run the rest of the (now) pointless for loop
            }
          }

          if (flag){
            shift->setDriverId(driver->getId());

            driver->addShift(shift);
            driver->sortShifts();
            driver->setWorkHours(workHours+shiftTime);
            //and update our local var workHours
            workHours = driver->getWorkHours();
          }
        }
      }
    }
  }

  std::cout << "Turnos da Linha " << id << " atribuídos com sucesso!" << std::endl;
  wait_for_enter();
}

void Line::resetWeekShifts(vector<Driver> *drivers,int wait){
    int i;

    for(i=0;i<shifts.size();i++)
        shifts.at(i).setDriverId(0);

    for(i=0;i< drivers->size();i++){
        drivers->at(i).removeShifts(id);
    }

    std::cout << "Turnos da Linha " << id << " reiniciados com sucesso!" << std::endl;
    if(wait)
      wait_for_enter();
}

void Line::printShift(){
  std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
    for(Shift s : shifts){
        std::cout << DayofWeek(s.getStartTime()) << " -> " << hour_string(s.getStartTime()) << " <-> " << hour_string(s.getEndTime()) << " --- Autocarro " << s.getBusOrderNumber();
        if(s.getDriverId() == 0)
          std::cout << "| Sem Condutor" << std::endl;
        else
          std::cout << "| Condutor -> " << s.getDriverId() << std::endl;
      }
    wait_for_enter();
}

void Line::printLine(){
    int i=0;
    std::cout << "Linha " << id << std::endl;
    std::cout << "Frequência = " << freq << " minutos" << std::endl;
    for(std::string s : busStopList){
        if(i)
            std::cout << " - " << s;
        else
            std::cout << s;
        i++;
    }
    std::cout << std::endl << std::endl;
}
