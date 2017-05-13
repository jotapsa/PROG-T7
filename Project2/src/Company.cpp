#include <limits.h> //INT_MAX
#include <map>
#include <algorithm> //sort
#include <iomanip> //setw
#include <fstream>
#include "semprarrolar.h"
#include "Shift.h"
#include "Bus.h"
#include <utility>
#include <sstream>
#include "Company.h"


Company::Company(string nome, string fichCondutores, string fichLinhas){
    this->nome = nome;
    this->fichCondutores = fichCondutores;
    this->fichLinhas = fichLinhas;
    std::string line;
    std::fstream file;
    file.open(fichLinhas,std::ios::in);
    if(!file.is_open()){
        std::cout << "File not found!" << std::endl;
        return ;
    }

    while(getline(file,line)){
        lines.push_back(Line(line));
    }
    file.close();
    ordenarLinhas();

    file.open(fichCondutores,std::ios::in);
    if(!file.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }

    while(getline(file,line)){
        drivers.push_back(Driver(line));
    }
    file.close();
    ordenarCondutores();
};

////////////////////////////////
// metodos get
///////////////////////////////
string Company::getNome() const{
  return nome;
}

vector<Line> Company::getLines() const{
    return lines;
}

vector<Driver> Company::getDrivers() const{
    return drivers;
}

//////////////////////////////
// metodos set
/////////////////////////////

////////////////////////////
// outros metodos
///////////////////////////
bool Company::sort_linha (Line i,Line j) {
    return (i.getId() < j.getId());
}

void Company::ordenarLinhas(){
    sort(lines.begin(),lines.end(),sort_linha);
}

bool Company::sort_condutor (Driver i,Driver j) {
    return (i.getId() < j.getId());
}
void Company::ordenarCondutores(){
    sort(drivers.begin(),drivers.end(),sort_condutor);
}

void Company::printLines(){
    std::cout << "************************" << " Linhas " << "************************" << std::endl;
    std::cout << std::endl;
    for(Line l : lines){
        l.printLine();
    }
    wait_for_enter();
}

void Company::printDrivers(){
    std::cout << "************************" << " Condutores " << "************************" << std::endl;
    std::cout << std::endl;
    for(Driver d : drivers){
        d.printDriver();
    }
    wait_for_enter();
}

bool Company::checkForLine(unsigned int id){
    for(Line l : lines){
        if(id == l.getId())
            return true;
    }
    return false;
}

int Company::newLine(bool *changed){
    Line *nova = new Line();

    int stops,tempo,id;
    std::string paragem;
    std::cout << "************************" << " Nova Linha " << "************************" << std::endl;
    do{
        ask_int("ID: ",&id);
    }while(id <= 0);

    if(checkForLine(id)){
        std::cout << "Linha " << id << " já existe!" << std::endl;
        wait_for_enter();
        return 1;
    }
    nova->setId(id);

    do{
        ask_int("Frequência (minutos): ",&tempo);
    }while(tempo <= 0);
    nova->setFreq(tempo);

    do{
        do{
            ask_int("Nº de Paragens: ",&stops);
        }while(stops <= 0);

        if(stops < 2){
            std::cout << "Uma linha tem no mínimo 2 paragens!" << std::endl;
            wait_for_enter();
        }
    }while(stops < 2);

    std::cin.ignore(INT_MAX,'\n');

    for(int i=0;i<stops;i++){
        do{
            std::cout << i+1 << "ª Paragem: ";
            getline(std::cin,paragem);
        }while(paragem.length() <= 0 || nova->checkStop(paragem));
        nova->addStop(paragem);
    }

    for(int i=0;i<stops-1;i++){
        do{
        ask_int("Tempo entre " + nova->getBusStops().at(i) + " e " + nova->getBusStops().at(i+1) + " (minutos): ",&tempo);
        }while(tempo <= 0);
        nova->addTime(tempo);
    }

    lines.push_back(*nova);
    std::cout << "Linha " << nova->getId() << " adicionada com sucesso!" << std::endl;
    *changed = true;
    ordenarLinhas();
    wait_for_enter();
    return 0;
}

int Company::displayLines(std::string Title){
    int i=1;
    std::cout << "************************ " << Title << " ************************" << std::endl;
    for(Line l : lines){
        std::cout << i << " - " << l.getId() << std::endl;
        i++;
    }
    std::cout << i << " - " << "Voltar" << std::endl;
    return i;
}

int Company::changeLine(bool *changed){
    int i,op=0,mod=0;
    do {
        ordenarLinhas();
        mod=0;
        i = displayLines("Alterar Linha");
        op = option(1,i, true);
        if(!op)
            return 1;
        lines.at(op-1).change(changed,&drivers);
    }while(1);
    return 0;

}

int Company::removeLine(bool *changed){
    int op,i;
    i = displayLines("Remover Linha");
    op = option(1,i, false);
    if(!op)
        return 1;

    lines.erase(lines.begin() + (op-1));
    std::cout << "Linha removida com sucesso!" << std::endl;
    *changed = true;
    wait_for_enter();
    return 0;
}

bool Company::checkForDriver(int ID){
    for(Driver d : drivers){
        if(ID == d.getId())
            return true;
    }
    return false;
}

int Company::newDriver(bool *changed){
    Driver *novo = new Driver();
    std::string nome;
    int aux;
    std::cout << "************************" << " Novo Condutor " << "************************" << std::endl;
    do{
        ask_int("ID: ", &aux);
    }while(aux <= 0);

    if(checkForDriver(aux)){
        std::cout << "Condutor " << aux << " já existe!" << std::endl;
        wait_for_enter();
        return 1;
    }
    novo->setId(aux);

    std::cin.ignore(INT_MAX,'\n');

    do{
        std::cout << "Nome: ";
        getline(std::cin,nome);
    }while(nome.length() <=0);
    novo->setName(nome);

    do{
        ask_int("Máximo de Horas por Turno: ", &aux);
    }while(aux <= 0);
    novo->setMaxHours(aux);

    do{
        ask_int("Máximo de Horas por Semana: ", &aux);
    }while(aux <= 0);
    novo->setMaxWeekWorkingTime(aux);

    do{
        ask_int("Mínimo de Horas por Descanso: ", &aux);
    }while(aux <= 0);
    novo->setMinRestTime(aux);

    drivers.push_back(*novo);
    std::cout << "Condutor " << novo->getId() << " adicionado com sucesso!" << std::endl;
    *changed = true;
    ordenarCondutores();
    wait_for_enter();
    return 0;
}

int Company::displayDrivers(){
    int i=1;
    std::cout << "************************" << " Condutores " << "************************" << std::endl;
    for(Driver d : drivers){
        std::cout << i << " - " << d.getName() << std::endl;
        i++;
    }
    std::cout << i << " - " << "Voltar" << std::endl;
    return i;
}

int Company::changeDriver(bool *changed){
    int i=1,op=0,aux,parametro;
    Driver *driver;
    std::string nome;

    do {
        i=displayDrivers();
        op = option(1,i, true);
        if(!op)
            return 1;
        driver = &drivers.at(op-1);

        std::cout << "************************" << " " << driver->getName() << " (" << driver->getId() << ") " << "************************" << std::endl;
        std::cout << "1 - ID\n" << "2 - Nome\n" << "3 - Máximo de Horas por Turno\n" << "4 - Máximo de Horas por Semana\n" << "5 - Mínimo de Horas por Descanso\n" << "6 - Voltar\n";

        parametro = option(1,6, true);
        if(!parametro)
            continue;

        switch(parametro){
            case 1:
                do{
                    std::cout << "ID atual -> " << driver->getId() << std::endl;
                    ask_int("ID novo -> ", &aux);
                    if(aux <= 0){
                        std::cout << "ID tem de ser positivo!" << std::endl << std::endl;
                        continue;
                    }
                    else if(!checkForDriver(aux)){
                        driver->setId(aux);
                        break;
                    }
                    else
                        std::cout << "Condutor " << aux << " já existe!" << std::endl;
                    std::cout << std::endl;
                }while(1);
                break;
            case 2:
                do{
                    std::cout << "Nome atual -> " << driver->getName() << std::endl;
                    std::cout << "Nome novo -> ";
                    getline(std::cin,nome);
                }while(nome.length() <= 0);
                driver->setName(nome);
                break;
            case 3:
                do{
                    std::cout << "Máximo de Horas por Turno atual -> " << driver->getMaxHours()/60 << std::endl;
                    ask_int("Máximo de Horas por Turno -> ", &aux);
                    if(aux > 0){
                        driver->setMaxHours(aux);
                        break;
                    }
                    else
                        std::cout << "Número de Horas tem de ser positivo!" << std::endl << std::endl;
                }while(1);
                break;
            case 4:
                do{
                    std::cout << "Máximo de Horas por Semana atual -> " << driver->getMaxWeekWorkingTime()/60 << std::endl;
                    ask_int("Máximo de Horas por Semana -> ", &aux);
                    if(aux > 0){
                        driver->setMaxWeekWorkingTime(aux);
                        break;
                    }
                    else
                        std::cout << "Número de Horas tem de ser positivo!" << std::endl << std::endl;
                }while(1);
                break;
            case 5:
                do{
                    std::cout << "Mínimo de Horas por Descanso atual -> " << driver->getMinRestTime()/60 << std::endl;
                    ask_int("Mínimo de Horas por Descanso -> ", &aux);
                    if(aux > 0){
                        driver->setMinRestTime(aux);
                        break;
                    }
                    else
                        std::cout << "Número de Horas tem de ser positivo!" << std::endl << std::endl;
                }while(1);
                break;
            default:
                break;
        }
        std::cout << "Condutor " << driver->getId() << " alterado com sucesso!" << std::endl;
        *changed = true;
        ordenarCondutores();
        wait_for_enter();
        return 0;
    }while(1);

}

int Company::removeDriver(bool *changed){
    int op=0,i;
    i = displayDrivers();
    op = option(1,i, false);
    if(!op)
        return 1;

    drivers.erase(drivers.begin() + (op-1));
    std::cout << "Condutor removido com sucesso!" << std::endl;
    *changed = true;
    wait_for_enter();
    return 0;
}

int Company::printSchedules(){
    int op,i;
    do{
        std::cout << "************************" << " Horários " << "************************" << std::endl;
        std::cout << "1 - Linha\n" << "2 - Paragem\n" << "3 - Voltar\n";
        op = option(1,3, true);
        if(!op)
            return 1;
        switch(op){
            case 1:
                i = displayLines("Linhas");
                op = option(1,i, true);
                if(!op)
                    return 1;

                lines.at(op-1).lineSchedule();
                break;
            case 2:
                stopSchedule();
                break;
            default:
                break;
        }
    }while(1);
    return 0;
}

bool sort_paragem (std::string i,std::string j) {
    return (i<j);
}

void ordenar_paragens(std::vector<std::string> *Paragens){
    sort(Paragens->begin(),Paragens->end(),sort_paragem);
}

int Company::stopSchedule(){
    std::vector<std::string> Paragens;
    std::vector<Line> LinhasParagem;
    int i=1,op=0,indice = 0;
    std::string paragem;

    for(Line l : lines){
        for(int i=0;i<l.getBusStops().size();i++){
            if(std::find(Paragens.begin(),Paragens.end(),l.getBusStops().at(i)) == Paragens.end())
                Paragens.push_back(l.getBusStops().at(i));
        }
    }
    ordenar_paragens(&Paragens);

    std::cout << "************************" << " Paragens " << "************************" << std::endl;
    for(std::string s : Paragens){
        std::cout << i << " - " << s << std::endl;
        i++;
    }
    std::cout << i << " - " << "Voltar" << std::endl;
    op = option(1,i, true);
    if(!op)
        return 1;
    paragem = Paragens.at(op-1);

    for(Line l : lines){
        if(l.checkStop(paragem))
            LinhasParagem.push_back(l);
    }

    for(Line l : LinhasParagem){
        //SENTIDO FIRST -> LAST
        std::cout << "************************" << " Linha " << l.getId() << " " << "************************" << std::endl;
        std::cout << std::endl;
        std::cout << std::setw(20) << "Sentido " << l.getBusStops().at(0) << " -> " << l.getBusStops().at(l.getBusStops().size()-1) << std::endl;
        std::cout << std::endl;

        indice = l.getIndexParagem(paragem);

        l.printTrip(indice,(int)l.getBusStops().size()-1,1);
        std::cout << std::endl;

        //SENTIDO LAST -> FIRST
        std::cout << "************************" << " Linha " << l.getId() << " " << "************************" << std::endl;
        std::cout << std::endl;
        std::cout << std::setw(20) << "Sentido " << l.getBusStops().at(l.getBusStops().size()-1) << " -> " << l.getBusStops().at(0) << std::endl;
        std::cout << std::endl;

        l.printTrip(indice,0,-1);
        std::cout << std::endl;
    }
    wait_for_enter();
    return 0;
}

int Company::searchTrip(){
    int direction,direction2,a=0,b = 0,c,d,tripsFound=0;
    std::vector<Line> LinhasOrigem,LinhasDestino,LinhasDiretas;
    std::string origem,destino;
    std::stringstream trip;
    std::map<int, std::string> trips;

    std::cout << "Origem: ";
    getline(std::cin,origem);
    std::cout << "Destino: ";
    getline(std::cin,destino);

    for(Line l : lines){
        if(l.checkStop(origem))
            LinhasOrigem.push_back(l);
        if(l.checkStop(origem) && l.checkStop(destino))
            LinhasDiretas.push_back(l);
    }

    if(!LinhasOrigem.size()){
        std::cout << "Não existe nenhuma linha com a paragem '" << origem << "'!\n";
        wait_for_enter();
        return 0;
    }

    //Linhas Diretas
    if((unsigned int) LinhasDiretas.size()){
      for(Line l : LinhasDiretas){
          std::cout << std::endl;
          //SENTIDO ORIGEM -> DESTINO
          a = (int) l.getIndexParagem(origem);
          b = (int) l.getIndexParagem(destino);
          direction = a < b ? 1 : -1;

          trip << "*****************" << " Linha " << l.getId() << " -> " << l.tripTime(a,b,direction) << " minutos "<< "************************" << std::endl;

          //l.printTrip(a, b, direction);
          tripsFound++;
          trips[l.tripTime(a,b,direction)] = std::string(trip.str());
          trip.str();
          trip.clear();
          //trips.insert(std::pair<std::string,int>(,l.tripTime(a,b,direction)))
      }
    }

    //Multi-Linha
    for(Line o : LinhasOrigem){
      for(std::string s : o.getBusStops()){
        for(Line l : lines){
          if(l.getId() == o.getId())
            continue;
          if(l.checkStop(s) && l.checkStop(destino)){
            //SENTIDO A -> B
            a = (int) o.getIndexParagem(origem);
            b = (int) o.getIndexParagem(s);
            direction = a < b ? 1 : -1;
            //l.printTrip(a, b, sentido);

            //SENTIDO B -> C
            c = (int) l.getIndexParagem(s);
            d = (int) l.getIndexParagem(destino);
            direction2 = a < b ? 1 : -1;

            if(o.tripTime(a,b,direction) && l.tripTime(c,d,direction2)){
              trip << "****" << " Linha " << o.getId() << " -> " << o.tripTime(a,b,direction) << " minutos ";
              trip << " + " << " Linha " <<  l.getId() << " -> " << l.tripTime(c,d,direction2) << " minutos " << "****";
              tripsFound++;
              trips[o.tripTime(a,b,direction) + l.tripTime(c,d,direction2)] = std::string(trip.str());
              trip.str();
              trip.clear();
            }
            //l.printTrip(a, b, sentido);
          }
        }
      }
    }
    if(!tripsFound)
      std::cout << "Não existe nenhum percurso possível entre " << origem << " e " << destino << "!\n";
    else{
      for( map<int,std::string>::iterator ii=trips.begin(); ii!=trips.end(); ++ii){
       std::cout << (*ii).second << std::endl;
   }

    }
    wait_for_enter();
    return 0;
}

void Company::updateLines(){
    int i;
    fstream file;
    file.open(fichLinhas,std::ios::out | std::ios::trunc);
    if(!file.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }

    for(Line l : lines){
        file << l.getId() << " ; " << l.getFreq() << " ; ";
        for(i=0;i < l.getBusStops().size()-1;i++)
            file << l.getBusStops().at(i) << ", ";
        file << l.getBusStops().at(i) << "; ";

        for(i=0;i < l.getTimings().size()-1;i++)
            file << l.getTimings().at(i) << ", ";
        file << l.getTimings().at(i);
        file << std::endl;
    }
    file.close();
}

void Company::updateDrivers(){
    fstream file;
    file.open(fichCondutores,std::ios::out | std::ios::trunc);
    if(!file.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }

    for(Driver d : drivers){
        file << d.getId() << " ; " << d.getName() << " ; " << (int)(d.getMaxHours()/60) << " ; " << (int)(d.getMaxWeekWorkingTime()/60) << " ; " << (int)(d.getMinRestTime()/60);
        file << std::endl;
    }
    file.close();
}

void Company::generateShifts(){
    int i,op;
    Line *linha;
    i = displayLines("Linhas");
    op = option(1,i, true);
    if(!op)
        return;
    linha = &lines.at(op-1);
    linha->generateWeekShifts(&drivers);
}

void Company::resetShifts(){
    int i,op;
    Line *linha;
    i = displayLines("Linhas");
    op = option(1,i, false);
    if(!op)
        return;
    linha = &lines.at(op-1);
    linha->resetWeekShifts(&drivers,1);
}

void Company::printShifts(){
  int op;
  std::cout << "************************" << " Turnos " << "************************" << std::endl;
  std::cout << "1 - Linha\n" << "2 - Condutor\n" << "3 - Voltar\n";

  op = option(1,3, true);

  if(!op){
    return;
  }

  switch(op){
    case 1:{
      printLineShift();
    }
    break;

    case 2:{
      printDriverShift();
    }
    break;
  }
}

void Company::printLineShift(){
    int i,op;
    Line *linha;
    i = displayLines("Linhas");
    op = option(1,i, true);
    if(!op)
        return;
    linha = &lines.at(op-1);
    linha->printShift();
}

void Company::printDriverShift(){
    int i,op;
    Driver *condutor;
    i = displayDrivers();
    op = option(1,i, true);
    if(!op)
        return;
    condutor = &drivers.at(op-1);
    condutor->printShift();
}
