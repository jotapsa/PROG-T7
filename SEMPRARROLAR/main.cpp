//
//  main.cpp
//  Projeto
//
//  Created by Bernardo Barbosa and Joao Sa.
//  Copyright © 2017 Bernardo Barbosa & Joao Sa. All rights reserved.
//

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
 Função responsável pela impressão do menu principal e dos respetivos sub-menus.
 */


/*
 Função main.
 */
int main(int argc, const char * argv[]) {
    Empresa Company = *new Empresa("Semprarrolar","condutores.txt","linhas.txt");
    int op=0;
    
    printf("\033c");
    while(1){
        op = imprimir_menu(menu);
        switch(menu){
            case 0:
                //UPDATE AOS FICHEIROS TXT
                if(!op){
                    if(update_linhas)
                        Company.atualizarLinhas();
                    if(update_condutores)
                         Company.atualizarCondutores();
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
                        Company.novaLinha(&update_linhas);
                        break;
                    case 2:
                        Company.alterarLinha(&update_linhas);
                        break;
                    case 3:
                        if(Company.removerLinha(&update_linhas))
                            printf("\033c");
                        break;
                    case 4:
                        Company.imprimirLinhas();
                        break;
                }
                break;
            case 2:
                switch(op){
                    case 0:
                        menu = 0;
                        break;
                    case 1:
                        Company.novoCondutor(&update_condutores);
                        break;
                    case 2:
                        Company.alterarCondutor(&update_condutores);
                        break;
                    case 3:
                        Company.removerCondutor(&update_condutores);
                        break;
                    case 4:
                        Company.imprimirCondutores();
                        break;
                }
                break;
            case 3:
                switch(op){
                    case 0:
                        menu = 0;
                        break;
                    case 1:
                        Company.imprimirHorarios();
                        break;
                    case 2:
                        Company.PercursoParagens();
                        break;
                }
                break;
            case 4:
                wait_for_enter();
                menu = 0;
                break;
            default:
                break;
        }
    }
    return 0;
}
