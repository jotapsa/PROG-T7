#include <iostream>

#include "semprarrolar.h"
#include "menu.h"

void mainMenu (appState &state){
    int choice;

    std::cout << "*******************************\n";
    std::cout << " 1 - Gestao de linhas.\n";
    std::cout << " 2 - Gestao de condutores.\n";
    std::cout << " 3 - Visualizacao de informacao.\n";
    std::cout << " 4 - Sair.\n";
    std::cout << " Digite a sua opcao e carregue ENTER: ";
    std::cin >> choice;
    std::cout << "\n";

    switch (choice) {
        case 1:
            changeState (state, ManageLines);
        break;
        case 2:
            changeState (state, ManageDrivers);
        break;
        case 3:
            changeState (state, ViewInf);
        break;
        case 4:
            changeState (state, Quit);
        break;
        default:
        break;
    }
}

void editLineMenu (appState &state, std::vector<Line> &lines){

    int choice;

    std::cout << "*******************************\n";
    std::cout << " 1 - Criar uma linha.\n";
    std::cout << " 2 - Editar uma linha.\n";
    std::cout << " 3 - Remover uma linha.\n";
    std::cout << " 4 - Sair para o Menu.\n";
    std::cout << " Digite a sua opcao e carregue ENTER: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            createLine (lines);
        break;
        case 2:
            //editLine (lines);
        break;
        case 3:
            //removeLine (lines);
        break;
        case 4:
            changeState (state, Menu);
        break;
        default:
        break;
    }
}
