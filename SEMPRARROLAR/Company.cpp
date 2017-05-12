#include "Company.h"


Empresa::Empresa(string nome, string fichCondutores, string fichLinhas){
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
        lines.push_back(*new Line(line));
    }
    file.close();
    ordenarLinhas();
    
    file.open(fichCondutores,std::ios::in);
    if(!file.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }
    
    while(getline(file,line)){
        drivers.push_back(*new Driver(line));
    }
    file.close();
    ordenarCondutores();
};

////////////////////////////////
// metodos get
///////////////////////////////
string Empresa::getNome() const{
  return nome;
}

vector<Line> Empresa::getLines() const{
    return lines;
}

vector<Driver> Empresa::getDrivers() const{
    return drivers;
}

//////////////////////////////
// metodos set
/////////////////////////////

////////////////////////////
// outros metodos
///////////////////////////
void Empresa::distribuiServico(){
}

bool Empresa::sort_linha (Line i,Line j) {
    return (i.getId() < j.getId());
}

void Empresa::ordenarLinhas(){
    sort(lines.begin(),lines.end(),sort_linha);
}

bool Empresa::sort_condutor (Driver i,Driver j) {
    return (i.getId() < j.getId());
}
void Empresa::ordenarCondutores(){
    sort(drivers.begin(),drivers.end(),sort_condutor);
}

void Empresa::imprimirLinhas(){
    int i=0;
    std::cout << "************************" << " Linhas " << "************************" << std::endl;
    std::cout << std::endl;
    for(Line l : lines){
        std::cout << "Linha " << l.getId() << std::endl;
            std::cout << "Frequência = " << l.getFreq() << " minutos" << std::endl;
            for(std::string s : l.getBusStops()){
                if(i)
                    std::cout << " - " << s;
                else
                    std::cout << s;
                i++;
            }
            std::cout << std::endl << std::endl;
        i=0;
    }
    wait_for_enter();
}

void Empresa::imprimirCondutores(){
    std::cout << "************************" << " Condutores " << "************************" << std::endl;
    std::cout << std::endl;
    for(Driver d : drivers){
        std::cout << "(" << d.getId() << ") " << d.getName() <<std::endl;
        std::cout << "Máximo de Horas por Turno: " << d.getMaxHours()/60 << std::endl;
        std::cout << "Máximo de Horas por Semana: " << d.getMaxWeekWorkingTime()/60 << std::endl;
        std::cout << "Mínimo de Horas por Descanso: " << d.getMinRestTime()/60 << std::endl;
        std::cout << "Não tem trabalho atribuído." << std::endl;
        std::cout << std::endl;
    }
    wait_for_enter();
}

bool Empresa::verificarLinha(int ID){
    for(Line l : lines){
        if(ID == l.getId())
            return true;
    }
    return false;
}

int Empresa::novaLinha(bool *changed){
    Line nova = *new Line();
    
    int stops,tempo,id;
    std::string paragem;
    std::cout << "************************" << " Nova Linha " << "************************" << std::endl;
    do{
        ask_int("ID: ",&id);
    }while(id <= 0);
    
    if(verificarLinha(id)){
        std::cout << "Linha " << id << " já existe!" << std::endl;
        wait_for_enter();
        return 1;
    }
    nova.setId(id);
    
    do{
        ask_int("Frequência (minutos): ",&tempo);
    }while(tempo <= 0);
    nova.setFreq(tempo);
    
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
        }while(paragem.length() <= 0 || nova.verificarParagem(paragem));
        nova.addStop(paragem);
    }
    
    for(int i=0;i<stops-1;i++){
        do{
        ask_int("Tempo entre " + nova.getBusStops().at(i) + " e " + nova.getBusStops().at(i+1) + " (minutos): ",&tempo);
        }while(tempo <= 0);
        nova.addTime(tempo);
    }
    
    lines.push_back(nova);
    std::cout << "Linha " << nova.getId() << " adicionada com sucesso!" << std::endl;
    *changed = true;
    ordenarLinhas();
    wait_for_enter();
    return 0;
}

int Empresa::displayLinhas(std::string Title){
    int i=1;
    std::cout << "************************ " << Title << " ************************" << std::endl;
    for(Line l : lines){
        std::cout << i << " - " << l.getId() << std::endl;
        i++;
    }
    std::cout << i << " - " << "Voltar" << std::endl;
    return i;
}

int Empresa::alterarLinha(bool *changed){
    int i,op=0,mod=0;
    do {
        ordenarLinhas();
        mod=0;
        i = displayLinhas("Alterar Linha");
        op = opcao(1,i,1);
        if(!op)
            return 1;
        lines.at(op-1).Alterar(changed);
    }while(1);
    return 0;

}

int Empresa::removerLinha(bool *changed){
    int op,i;
    i = displayLinhas("Remover Linha");
    op = opcao(1,i,0);
    if(!op)
        return 1;
    
    lines.erase(lines.begin() + (op-1));
    std::cout << "Linha removida com sucesso!" << std::endl;
    *changed = true;
    wait_for_enter();
    return 0;
}

bool Empresa::verificarCondutor(int ID){
    for(Driver d : drivers){
        if(ID == d.getId())
            return true;
    }
    return false;
}

int Empresa::novoCondutor(bool *changed){
    Driver novo = *new Driver();
    std::string nome;
    int aux;
    std::cout << "************************" << " Novo Condutor " << "************************" << std::endl;
    do{
        ask_int("ID: ", &aux);
    }while(aux <= 0);
    
    if(verificarCondutor(aux)){
        std::cout << "Condutor " << aux << " já existe!" << std::endl;
        wait_for_enter();
        return 1;
    }
    novo.setId(aux);
    
    std::cin.ignore(INT_MAX,'\n');
    
    do{
        std::cout << "Nome: ";
        getline(std::cin,nome);
    }while(nome.length() <=0);
    novo.setName(nome);
    
    do{
        ask_int("Máximo de Horas por Turno: ", &aux);
    }while(aux <= 0);
    novo.setMaxHours(aux);
    
    do{
        ask_int("Máximo de Horas por Semana: ", &aux);
    }while(aux <= 0);
    novo.setMaxWeekWorkingTime(aux);
    
    do{
        ask_int("Mínimo de Horas por Descanso: ", &aux);
    }while(aux <= 0);
    novo.setMinRestTime(aux);
    
    drivers.push_back(novo);
    std::cout << "Condutor " << novo.getId() << " adicionado com sucesso!" << std::endl;
    *changed = true;
    ordenarCondutores();
    wait_for_enter();
    return 0;
}

int Empresa::displayCondutores(){
    int i=1;
    std::cout << "************************" << " Condutores " << "************************" << std::endl;
    for(Driver d : drivers){
        std::cout << i << " - " << d.getName() << std::endl;
        i++;
    }
    std::cout << i << " - " << "Voltar" << std::endl;
    return i;
}

int Empresa::alterarCondutor(bool *changed){
    int i=1,op=0,aux,parametro;
    Driver *driver;
    std::string nome;
    
    do {
        i=displayCondutores();
        op = opcao(1,i,1);
        if(!op)
            return 1;
        driver = &drivers.at(op-1);
        
        std::cout << "************************" << " " << driver->getName() << " (" << driver->getId() << ") " << "************************" << std::endl;
        std::cout << "1 - ID\n" << "2 - Nome\n" << "3 - Máximo de Horas por Turno\n" << "4 - Máximo de Horas por Semana\n" << "5 - Mínimo de Horas por Descanso\n" << "6 - Voltar\n";
        
        parametro = opcao(1,6,1);
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
                    else if(!verificarCondutor(aux)){
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
                    std::cout << "Máximo de Horas por Turno atual -> " << driver->getMaxHours() << std::endl;
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
                    std::cout << "Máximo de Horas por Semana atual -> " << driver->getMaxWeekWorkingTime() << std::endl;
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
                    std::cout << "Mínimo de Horas por Descanso atual -> " << driver->getMinRestTime() << std::endl;
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

int Empresa::removerCondutor(bool *changed){
    int op=0,i;
    i = displayCondutores();
    op = opcao(1,i,0);
    if(!op)
        return 1;
    
    drivers.erase(drivers.begin() + (op-1));
    std::cout << "Condutor removido com sucesso!" << std::endl;
    *changed = true;
    wait_for_enter();
    return 0;
}

int Empresa::imprimirHorarios(){
    int op,i;
    do{
        std::cout << "************************" << " Horários " << "************************" << std::endl;
        std::cout << "1 - Linha\n" << "2 - Paragem\n" << "3 - Voltar\n";
        op = opcao(1,3,1);
        if(!op)
            return 1;
        switch(op){
            case 1:
                i = displayLinhas("Linhas");
                op = opcao(1,i,1);
                if(!op)
                    return 1;
                
                lines.at(op-1).HorarioLinha();
                break;
            case 2:
                HorarioParagem();
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

int Empresa::HorarioParagem(){
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
    op = opcao(1,i,1);
    if(!op)
        return 1;
    paragem = Paragens.at(op-1);
    
    for(Line l : lines){
        if(l.verificarParagem(paragem))
            LinhasParagem.push_back(l);
    }
    
    for(Line l : LinhasParagem){
        //SENTIDO FIRST -> LAST
        std::cout << "************************" << " Linha " << l.getId() << " " << "************************" << std::endl;
        std::cout << std::endl;
        std::cout << std::setw(20) << "Sentido " << l.getBusStops().at(0) << " -> " << l.getBusStops().at(l.getBusStops().size()-1) << std::endl;
        std::cout << std::endl;
        
        indice = l.getIndexParagem(paragem);
        
        l.imprimirViagem(indice,(int)l.getBusStops().size()-1,1);
        std::cout << std::endl;
        
        //SENTIDO LAST -> FIRST
        std::cout << "************************" << " Linha " << l.getId() << " " << "************************" << std::endl;
        std::cout << std::endl;
        std::cout << std::setw(20) << "Sentido " << l.getBusStops().at(l.getBusStops().size()-1) << " -> " << l.getBusStops().at(0) << std::endl;
        std::cout << std::endl;
        
        l.imprimirViagem(indice,0,-1);
        std::cout << std::endl;
    }
    wait_for_enter();
    return 0;
}

int Empresa::PercursoParagens(){
    int sentido,a=0,b = 0;
    std::vector<Line> LinhasPercurso;
    std::string origem,destino;
    
    std::cout << "Origem: ";
    getline(std::cin,origem);
    std::cout << "Destino: ";
    getline(std::cin,destino);
    
    for(Line l : lines){
        if(l.verificarParagem(origem) && l.verificarParagem(destino))
            LinhasPercurso.push_back(l);
    }
    
    if(!LinhasPercurso.size()){
        std::cout << "Não existe nenhum percurso entre " << origem << " e " << destino << "!\n";
    }
    
    for(Line l : LinhasPercurso){
        std::cout << std::endl;
        //SENTIDO ORIGEM -> DESTINO
        a = (int) l.getIndexParagem(origem);
        b = (int) l.getIndexParagem(destino);
        sentido = a < b ? 1 : -1;
        
        std::cout << "*****************" << " Linha " << l.getId() << " -> " << l.TempoParagens(a,b,sentido) << " minutos "<< "************************" << std::endl;
        
        l.imprimirViagem(a, b, sentido);
    }
    wait_for_enter();
    return 0;
}

void Empresa::atualizarLinhas(){
    int i;
    fstream file;
    file.open(fichLinhas,std::ios::out | std::ios::trunc);
    if(!file.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }
    
    for(Line l : lines){
        file << l.getId() << " ; " << l.getFreq() << " ; ";
        for(i=0;i < l.getBusStops().size()-2;i++)
            file << l.getBusStops().at(i) << ", ";
        file << l.getBusStops().at(i) << "; ";
        
        for(i=0;i < l.getTimings().size()-1;i++)
            file << l.getTimings().at(i) << ", ";
        file << l.getTimings().at(i);
        file << std::endl;
    }
    file.close();
}

void Empresa::atualizarCondutores(){
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

void Empresa::gerarTurnos(){
    int i,op;
    Line *linha;
    i = displayLinhas("Linhas");
    op = opcao(1,i,0);
    if(!op)
        return;
    linha = &lines.at(op-1);
    linha->gerarTurnosSemana(drivers);
}

void Empresa::reiniciarTurnos(){
    int i,op;
    Line *linha;
    i = displayLinhas("Linhas");
    op = opcao(1,i,0);
    if(!op)
        return;
    linha = &lines.at(op-1);
    linha->reiniciarTurnosSemana(drivers);
}

void Empresa::imprimirTurnoLinha(){
    int i,op;
    Line *linha;
    i = displayLinhas("Linhas");
    op = opcao(1,i,1);
    if(!op)
        return;
    linha = &lines.at(op-1);
    linha->imprimirTurno();
}

void Empresa::imprimirTurnoCondutor(){
    int i,op;
    Driver *condutor;
    i = displayCondutores();
    op = opcao(1,i,1);
    if(!op)
        return;
    condutor = &drivers.at(op-1);
    condutor->imprimirTurno();
}

