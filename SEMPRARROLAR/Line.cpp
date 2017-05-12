#include "Line.h"


Line::Line(string textLine){
    int i,day,viagens_dia,bus,n;
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
    
    //Shifts With Only Buses
    for(day=0;day<7;day++){
        for(i=START_DAY(day);i< END_DAY(day);i+=freq){
            shifts.push_back(*new Shift(id,i,i + getTempoTotalViagem()));
        }
    }
    
    viagens_dia = ((END - BEGIN)*60) / freq;
    n = (int) ((double) getTempoTotalViagem() / freq + 1.0);
    //Autocarros necessários
    for(i=1;i<=n;i++)
        buses.push_back(*new Bus(i,id));
    
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

int Line::getIndexParagem(std::string paragem) const{
    return (int) std::distance(busStopList.begin(), std::find(busStopList.begin(), busStopList.end(), paragem));
}

int Line::getBusStopsSize() const{
    return (int) busStopList.size();
}

vector<Bus> Line::getBuses() const{
    return buses;
}

int Line::getTempoTotalViagem(){
    return TempoParagens(0, getBusStopsSize()-1, 1)*2;
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

void Line::addStop (std::string paragem,unsigned int pos){
    int timeStop;
    
    if (pos != 0){
        ask_int("Tempo de viagem entre " + busStopList.at(pos-1) + " e " + paragem + " (minutos): ",&timeStop);
        timesList.insert(timesList.begin()+pos-1, timeStop);
    }
    
    if (pos != busStopList.size()){
        ask_int("Tempo de viagem entre " + paragem + " e " + busStopList.at(pos) + " (minutos): ",&timeStop);
        timesList.insert(timesList.begin()+pos, timeStop);
    }
    
    if (pos!=0 && pos != busStopList.size()){
        timesList.erase(timesList.begin()+pos+1);
    }
    
    busStopList.insert(busStopList.begin()+pos, paragem);
}

void Line::addStop (std::string paragem){
    busStopList.push_back(paragem);
}

void Line::addTime (int time){
    timesList.push_back(time);
}

bool Line::verificarParagem(std::string paragem){
    return (std::find(busStopList.begin(),busStopList.end(),paragem) != busStopList.end()) ? true : false;
}



int Line::TempoParagens(int origem,int destino,int sentido){
    if(sentido==1)
        return (int)std::accumulate(timesList.begin() + origem,timesList.begin() + destino,0);
    else
        return (int)std::accumulate(timesList.begin() + destino,timesList.begin() + origem,0);
}


void Line::alinharParagem(int origem,int paragem){
    int espaço;
    if(busStopList.at(paragem).length() < 6)
        espaço = 6;
    else
        espaço = (int)busStopList.at(paragem).length();
    
    if(paragem == origem)
        std::cout.width(espaço);
    else
        std::cout.width(espaço + 5);
}



void Line::imprimirViagem(int origem,int destino,int sentido){
    int time,hora_paragem,horas,minutos,viagem_completa,hora_saida;
    std::string hora;
    
    for(int s=origem;s!=destino+sentido;s+=sentido){
        alinharParagem(origem,s);
        std::cout << busStopList.at(s);
    }
    std::cout << std::endl;
    
    viagem_completa = TempoParagens(0, (int)busStopList.size()-1, 1);
    
    if(sentido==1)
        time = START_TIME;
    else
        time = START_TIME + viagem_completa;
    
    while(1){
        if(sentido==1)
            hora_paragem = time + TempoParagens(0, origem, 1);
        else
            hora_paragem = time + TempoParagens(origem, (int)busStopList.size()-1, 1);
        hora = hora_string(hora_paragem);
        alinharParagem(origem,origem);
        std::cout << hora;
        for(int j=origem;j!=destino;j+=sentido){
            if( (j==timesList.size() && sentido==1) || (j==0 && sentido==-1) )
                continue;
            if(sentido==1)
                hora_paragem += timesList.at(j);
            else
                hora_paragem += timesList.at(j+sentido);
            hora = hora_string(hora_paragem);
            alinharParagem(origem,j+sentido);
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



void Line::HorarioLinha(){
    
    //SENTIDO FIRST -> LAST
    std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
    std::cout << std::endl;
    std::cout << std::setw(20) << "Sentido " << busStopList.at(0) << " -> " << busStopList.at(busStopList.size()-1) << std::endl;
    std::cout << std::endl;
    
    imprimirViagem(0,(int)busStopList.size()-1,1);
    std::cout << std::endl;
    
    //SENTIDO LAST -> FIRST
    std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
    std::cout << std::endl;
    std::cout << std::setw(20) << "Sentido " << busStopList.at(busStopList.size()-1) << " -> " << busStopList.at(0) << std::endl;
    std::cout << std::endl;
    
    imprimirViagem((int)busStopList.size()-1,0,-1);
    wait_for_enter();
}

int Line::Alterar(bool *changed){
    int op,aux,mod = 1;
    do{
        std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
        std::cout << "1 - ID\n" << "2 - Frequência\n" << "3 - Paragens\n" << "4 - Tempo entre Paragens\n" << "5 - Voltar\n";
        
        op = opcao(1,5,1);
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
                mod = AlterarParagem();
                break;
            case 4:
                mod = AlterarTempos();
                break;
            default:
                break;
        }
        if(!mod){
            std::cout << "Linha " << id << " alterada com sucesso!" << std::endl;
            *changed = true;
            wait_for_enter();
        }
    }while(op);
    return 0;
}

int Line::AlterarParagem(){
    int i=1,op=0,paragem,pos;
    std::string nome;
    
    do{
        printf("\033c");
        i=1;
        std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
        std::cout << "1 - Adicionar Paragem\n" << "2 - Mudar Nome de Paragem\n" << "3 - Remover Paragem\n" << "4 - Voltar\n";
        op = opcao(1,4,1);
        if(!op)
            return 1;
        
        std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
        switch(op){
            case 1:
                std::cout << i << " - " << "Início de Linha" << std::endl;
                i++;
                for(int j=0;j<busStopList.size()-1;j++){
                    std::cout << i << " - Entre " << busStopList.at(j) << " e " << busStopList.at(j+1) << std::endl;
                    i++;
                }
                std::cout << i << " - " << "Fim de Linha" << std::endl;
                i++;
                
                std::cout << i << " - " << "Voltar" << std::endl;
                paragem = opcao(1,i,0);
                if(!paragem)
                    continue;
                
                do{
                    std::cout << "Nome da Paragem: ";
                    getline(std::cin, nome);
                }while(nome.length() <= 0 || verificarParagem(nome));
                addStop(nome, paragem-1);
                
                return 0;
            case 2:
                for(std::string s : busStopList){
                    std::cout << i << " - " << s << std::endl;
                    i++;
                }
                std::cout << i << " - " << "Voltar" << std::endl;
                paragem = opcao(1,i,0);
                if(!paragem)
                    continue;
                
                do{
                    std::cout << std::endl << "Nome de Paragem atual -> " << busStopList.at(paragem-1) << std::endl;
                    std::cout << "Nome de Paragem novo -> ";
                    getline(std::cin, nome);
                }while(nome.length() <= 0 || verificarParagem(nome));
                busStopList.at(paragem-1) = nome;
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
                paragem = opcao(1,i,0);
                if(!paragem)
                    continue;
                
                pos = paragem - 1;
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

int Line::AlterarTempos(){
    int i=1,op=0,tempo;
    std::cout << "************************" << " Linha " << id << " " << "************************" << std::endl;
    for(int j=0;j<busStopList.size()-1;j++){
        std::cout << i << " - Entre " << busStopList.at(j) << " e " << busStopList.at(j+1) << " (" << timesList.at(j) << " minutos)"<< std::endl;
        i++;
    }
    std::cout << i << " - " << "Voltar" << std::endl;
    op = opcao(1,i,0);
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

void Line::gerarTurnosSemana(vector<Driver> drivers){
    int n,i,day,viagens_dia,horas_semana,horas_turno,horas_descanso,turno_anterior;
    Shift *s;
    viagens_dia = ((END - BEGIN)*60) / freq;
    n = (int) ((double) getTempoTotalViagem() / freq + 1.0);
    
    for(Driver d : drivers){
        if(d.getMaxHours() < getTempoTotalViagem())
            continue;
        horas_semana = 0;
        turno_anterior = 0;
        for(day=0;day<7;day++){
            horas_turno = 0;
            horas_descanso = 0;
            if(horas_semana + getTempoTotalViagem() > d.getMaxWeekWorkingTime())
                break;
            for(i=0;i<viagens_dia;i++){
                s = &shifts.at(day*viagens_dia + i);
                
                if(s->getDriverId() != 0)
                    continue;
                
                if(turno_anterior + getTempoTotalViagem() > s->getStartTime())
                    continue;
                
                if((horas_turno + getTempoTotalViagem() > d.getMaxHours()) && (horas_descanso < d.getMinRestTime())){
                    horas_descanso += freq;
                    continue;
                }
                else if(horas_descanso >= d.getMinRestTime()){
                    horas_descanso = 0;
                    horas_turno = 0;
                }

                s->setDriverId(d.getId());
                d.getShifts().push_back(*s);
                horas_turno += getTempoTotalViagem();
                horas_semana += getTempoTotalViagem();
                turno_anterior = s->getStartTime();
                
                if(horas_semana + getTempoTotalViagem() > d.getMaxWeekWorkingTime())
                    break;
                }
            }
    }
    std::cout << "Turnos Atribuídos com sucesso!" << std::endl;
    wait_for_enter();
}

void Line::reiniciarTurnosSemana(vector<Driver> drivers){
    int i;
    for(Shift s : shifts)
        s.setDriverId(0);
    
    for(Driver d : drivers){
        for(i=0;i< d.getShifts().size();i++){
            if(d.getShifts().at(i).getBusLineId() == id)
                d.getShifts().erase(d.getShifts().begin() + i);
        }
    }
    std::cout << "Turnos Reiniciados com sucesso!" << std::endl;
    wait_for_enter();
}

void Line::imprimirTurno(){
    for(Shift s : shifts)
        std::cout << DiadaSemana(s.getStartTime()) << " -> " << hora_string(s.getStartTime()) << " <-> " << hora_string(s.getEndTime()) << " --- Autocarro " << s.getBusOrderNumber() << " Condutor -> " << s.getDriverId() << std::endl;
    wait_for_enter();
}
