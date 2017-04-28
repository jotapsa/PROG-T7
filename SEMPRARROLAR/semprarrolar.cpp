//
//  semprarrolar.cpp
//  SEMPRARROLAR
//
//  Created by Bernardo Barbosa on 27/04/17.
//  Copyright © 2017 Bernardo Barbosa. All rights reserved.
//

#include "semprarrolar.h"

void wait_for_enter(){
    std::cout << std::endl;
    std::cout << "Prima Enter para continuar...\n";
    system("read");
    printf("\033c");
}

void ask_int(std::string string, int *number){
    std::string invalid;
    do{
        std::cout << string;
        std::cin >> *number;
        if(std::cin.fail()){
            std::cin.clear();
            getline(std::cin,invalid);
            std::cout << "Introduza um número inteiro!\n";
            continue;
        }
        return;
    }while(1);
}

int opcao(int menor,int maior,int clear){
    int op;
    do{
        ask_int("Opção: ",&op);
    }while(op < menor || op > maior);
    std::cin.ignore(INT_MAX,'\n');
    
    if(clear)
        printf("\033c");
    if(op == maior)
        return 0;
    return op;
}

std::vector<std::string> split(const std::string &s, const char &delim){
    std::vector<std::string> splitStrings;
    std::istringstream inSStream(s);
    
    std::string partX;
    
    while (getline(inSStream, partX, delim)) {
        splitStrings.push_back (partX);
    }
    
    return splitStrings;
}

int imprimir_menu(int menu){
    std::fstream creditos;
    std::string s;
    printf("\033c");
    
    switch(menu){
        case 0:
            std::cout << "************************" << " SEMPRARROLAR " << "************************" << std::endl;
            std::cout << "1 - Gestão de Linhas\n" << "2 - Gestão de Condutores\n" << "3 - Visualização de Informação\n" << "4 - Créditos\n" << "5 - Sair\n";
            return opcao(1,5,1);
        case 1:
            std::cout << "************************" << " Gestão de Linhas " << "************************" << std::endl;
            std::cout << "1 - Criar Linha\n" << "2 - Alterar Linha\n" << "3 - Remover Linha\n" << "4 - Lista de Linhas\n" << "5 - Voltar\n";
            return opcao(1,5,1);
        case 2:
            std::cout << "************************" << " Gestão de Condutores " << "************************" << std::endl;
            std::cout << "1 - Criar Condutor\n" << "2 - Alterar Condutor\n" << "3 - Remover Condutor\n" << "4 - Lista de Condutores\n" << "5 - Voltar\n";
            return opcao(1,5,1);
        case 3:
            std::cout << "************************" << " Visualização de Informação " << "************************" << std::endl;
            //            std::cout << "1 - Horários\n" << "2 - Percursos\n" << "3 - Trabalho Condutor\n" << "4 - Voltar\n";
            std::cout << "1 - Horários\n" << "2 - Percursos\n" << "3 - Voltar\n";
            return opcao(1,3,1);
        case 4:
            creditos.open("README.txt",std::ios::in);
            if(!creditos.is_open()){
                std::cout << "File not found!" << std::endl;
                return 1;
            }
            while(getline(creditos,s))
                std::cout << s << std::endl;
            creditos.close();
            break;;
        default:
            break;
    }
    return 0;
}