#include "Driver.h"

Driver::Driver(string textLine){
    std::vector<std::string> splitStrings(split(textLine,';'));
    std::istringstream inSStream;
    
    //Check the size
    if (splitStrings.size() != 5){
        return;
    }
    
    //Remover espacos no inicio
    for (unsigned int i=0; i<splitStrings.size(); i++){
        if (splitStrings.at(i).at(0) == ' '){
            splitStrings.at(i).erase (splitStrings.at(i).begin());
        }
    }
    
    //Already know the first element is the id
    inSStream.str(splitStrings.at(0));
    inSStream.clear();
    inSStream >> id;
    
    //Second element is the name
    name = splitStrings.at(1);
    
    //Maximum hours per shift
    inSStream.str(splitStrings.at(2));
    inSStream.clear();
    inSStream >> maxHours;
    
    //Maximum hours per week
    inSStream.str(splitStrings.at(3));
    inSStream.clear();
    inSStream >> maxWeekWorkingTime;
    
    //Minimin hours between shifts
    inSStream.str(splitStrings.at(4));
    inSStream.clear();
    inSStream >> minRestTime;
    
    maxHours *= 60;
    maxWeekWorkingTime *= 60;
    minRestTime *= 60;
    atualHours=0;
}

Driver::Driver(){
    
}

//////////////
// get methods
//////////////

unsigned int Driver::getId() const{
  return id;
}

string Driver::getName() const{
  return name;
}

unsigned int Driver::getMaxHours() const{
  return maxHours;
}

unsigned int Driver::getMaxWeekWorkingTime() const{
  return maxWeekWorkingTime;
}

unsigned int Driver::getMinRestTime() const{
  return minRestTime;
}

vector<Shift> Driver::getShifts() const{
  return shifts;
}

unsigned int Driver::getAtualHours() const{
    return atualHours;
}

//////////////
// set methods
//////////////
void Driver::setId (unsigned int id) {
    this->id = id;
}
void Driver::setName (std::string name) {
    this->name = name;
}
void Driver::setMaxHours (unsigned int maxHours) {
    this->maxHours = maxHours*60;
}
void Driver::setMaxWeekWorkingTime (unsigned int maxWeekWorkingTime) {
    this->maxWeekWorkingTime = maxWeekWorkingTime*60;
}
void Driver::setMinRestTime (unsigned int minRestTime) {
    this->minRestTime = minRestTime*60;
}

void Driver::setAtualHours(unsigned int atualHours){
    this->atualHours = atualHours;
}

//////////////
// other methods
//////////////
void Driver::imprimirTurno(){
    if(shifts.size() == 0){
        std::cout << "Não tem turnos atribuídos!" << std::endl;
        wait_for_enter();
        return;
    }
    
    for(Shift s : shifts)
        std::cout << DiadaSemana(s.getStartTime()) << " -> " << hora_string(s.getStartTime()) << " <-> " << hora_string(s.getEndTime()) << " --- Autocarro " << s.getBusOrderNumber() << "| Linha -> " << s.getBusLineId() << std::endl;
    wait_for_enter();
}

void Driver::adicionarTurno(Shift *turno){
    shifts.push_back(*turno);
}

void Driver::removerTurnosLinha(int idLinha){
    int i;
    for(i=(int)shifts.size()-1;i>=0;i--){
        if(shifts.at(i).getBusLineId() == idLinha){
            atualHours -= (shifts.at(i).getEndTime() - shifts.at(i).getStartTime());
            shifts.erase(shifts.begin() + i);
        }
    }
}

void Driver::imprimirPerfil(){
    std::cout << "(" << id << ") " << name <<std::endl;
    std::cout << "Máximo de Horas por Turno: " << maxHours/60 << std::endl;
    std::cout << "Máximo de Horas por Semana: " << maxWeekWorkingTime/60 << std::endl;
    std::cout << "Mínimo de Horas por Descanso: " << minRestTime/60 << std::endl;
    std::cout << "Turnos Atribuídos: " << shifts.size() << std::endl;
    std::cout << "Tempo Por Atribuir : " << tempo_string(maxWeekWorkingTime - atualHours) << std::endl;
    std::cout << std::endl;
}

bool Driver::estadoCondutor(int start,int end){
    int i,turno = end - start,horas_turno=0,turno_atual,turno_proximo=0;
    bool ok = true;
    std::cout << "Testando ... " << hora_string(start) << " <-> " << hora_string(end) << std::endl;
    
    Shift teste = Shift(0,start,end);
    shifts.push_back(teste);
    ordenarTurnos();
    
    for(i=0;i<shifts.size();i++){
        //Verificar limites do condutor
        turno_atual = shifts.at(i).getEndTime() + shifts.at(i).getStartTime();
        horas_turno += turno_atual;
        if(i!= shifts.size()-1){
            
            turno_proximo = shifts.at(i+1).getEndTime() + shifts.at(i+1).getStartTime();
            
            if(horas_turno + turno_proximo > maxHours){
                horas_turno = 0;
                if(shifts.at(i+1).getStartTime() - shifts.at(i).getEndTime() < minRestTime){
                    ok = false;
                    std::cout << "falso" << hora_string(start) << " <-> " << hora_string(end) << std::endl;
                    break;
                }
                else
                    ok = true;
            }  
        }
    }
    for(i=0;shifts.at(i).getBusLineId() != 0;i++){}
    shifts.erase(shifts.begin() + i);
    std::cout << "Valor -> " << ok << std::endl;
    return ok;
    
        
//        if(i==0){
//            if(end < shifts.at(i).getStartTime()){
//                if(turno + (shifts.at(i).getEndTime() - shifts.at(i).getStartTime()) > maxHours){
//                    if(shifts.at(i).getStartTime() - end < minRestTime){
//                        free = false;
//                        horas_turno = shifts.at(i).getEndTime() - shifts.at(i).getStartTime();
//                    }
//                    else{
//                        free = true;
//                        horas_turno += turno + shifts.at(i).getEndTime() - shifts.at(i).getStartTime();
//                    }
//                }
//                else{
//                    free = true;
//                    horas_turno += turno + shifts.at(i).getEndTime() - shifts.at(i).getStartTime();
//                }
//            }
//        }
//        else if(i==shifts.size()-1){
//            if(start > shifts.at(i).getEndTime()){
//                if(turno + (shifts.at(i).getEndTime() - shifts.at(i).getStartTime()) > maxHours){
//                        if(start - shifts.at(i).getEndTime() < minRestTime){
//                            free = false;
//                            horas_turno = shifts.at(i).getEndTime() - shifts.at(i).getStartTime();
//                        }
//                        else{
//                            free = true;
//                            horas_turno += turno + shifts.at(i).getEndTime() - shifts.at(i).getStartTime();
//                        }
//                }
//                else{
//                    free = true;
//                    horas_turno += turno + shifts.at(i).getEndTime() - shifts.at(i).getStartTime();
//                }
//            }
//        }
//        else{
//            
//            
//        }
        
        
//        //ANTES
//        if(end < shifts.at(i).getStartTime()){
//            if(i==0){
//                if(turno + (shifts.at(i).getEndTime() - shifts.at(i).getStartTime() > maxHours)){
//                    if(shifts.at(i).getStartTime() - end < minRestTime){
//                        free = false;
//                        continue;
//                    }
//                    else
//                        free = true;
//                }
//            }
//            else{
//                
//                
//            }
//        }
//        
//        //DEPOIS
//        if(start > shifts.at(i).getEndTime()){
//            if(i==shifts.size()-1){
//                if(turno + (shifts.at(i).getEndTime() - shifts.at(i).getStartTime() > maxHours)){
//                    if(shifts.at(i).getEndTime() - start < minRestTime){
//                        free = false;
//                        continue;
//                    }
//                    else
//                        free = true;
//                }
//            }
//            else{
//                
//            }
//        }
//        
//        if(free)
//            break;
//    }
}

bool Driver::sort_shift (Shift i,Shift j) {
    return (i.getStartTime() < j.getStartTime());
}

void Driver::ordenarTurnos(){
    sort(shifts.begin(),shifts.end(),sort_shift);
}


