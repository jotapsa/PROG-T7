#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include "Line.h"
#include "Driver.h"
#include "Company.h"
#include "semprarrolar.h"

int menu=0;
bool update_linhas = false;
bool update_condutores = false;

/*
 Função main.
 */
int main(int argc, const char * argv[]) {
    Company *company = new Company("Semprarrolar","condutores.txt","linhas.txt");
    int op=0;

    printf("\033c");
    while(1){
        op = imprimir_menu(menu);
        switch(menu){
            case 0:
                //UPDATE AOS FICHEIROS TXT
                if(!op){
                    if(update_linhas)
                        company->atualizarLinhas();
                    if(update_condutores)
                         company->atualizarCondutores();
                    return 0;
                }
                else
                    menu = op;
                break;
            case 1:
                switch(op){
                    case 0:
                        menu = 0;
                        break;
                    case 1:
                        company->novaLinha(&update_linhas);
                        break;
                    case 2:
                        company->alterarLinha(&update_linhas);
                        break;
                    case 3:
                        if(company->removerLinha(&update_linhas))
                            printf("\033c");
                        break;
                    case 4:
                        company->imprimirLinhas();
                        break;
                }
                break;
            case 2:
                switch(op){
                    case 0:
                        menu = 0;
                        break;
                    case 1:
                        company->novoCondutor(&update_condutores);
                        break;
                    case 2:
                        company->alterarCondutor(&update_condutores);
                        break;
                    case 3:
                        company->removerCondutor(&update_condutores);
                        break;
                    case 4:
                        company->imprimirCondutores();
                        break;
                }
                break;
            case 3:
                switch(op){
                case 0:
                    menu = 0;
                    break;
                case 1:
                        company->gerarTurnos();
                    break;
                case 2:
                        company->reiniciarTurnos();
                    break;
                }
                break;
            case 4:
                switch(op){
                    case 0:
                        menu = 0;
                        break;
                    case 1:
                        company->imprimirHorarios();
                        break;
                    case 2:
                        company->PercursoParagens();
                        break;
                    case 3:
                        menu = 5;
                }
                break;
            case 5:
                switch(op){
                    case 0:
                        menu = 4;
                        break;
                    case 1:
                        company->imprimirTurnoLinha();
                        break;
                    case 2:
                        company->imprimirTurnoCondutor();
                        break;
                }
                break;
            case 6:
                wait_for_enter();
                menu = 0;
                break;
            default:
                break;
        }
    }
    return 0;
}
