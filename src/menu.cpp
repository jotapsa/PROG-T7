#include <iostream>

#include "semprarrolar.h"
#include "menu.h"

void mainMenu (appState &state){
    int choice;

    clearConsole();
    std::cout << "*******************************\n";
    std::cout << " 1 - Gestao de linhas.\n";
    std::cout << " 2 - Gestao de condutores.\n";
    std::cout << " 3 - Visualizacao de informacao.\n";
    std::cout << " 4 - Sair.\n";
    std::cout << " Digite a sua opcao e presse ENTER: ";
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

void manageLineMenu (appState &state, std::vector<Line> &lines){
    int choice;

    clearConsole();
    std::cout << "*******************************\n";
    std::cout << " 1 - Criar uma linha.\n";
    std::cout << " 2 - Editar uma linha.\n";
    std::cout << " 3 - Remover uma linha.\n";
    std::cout << " 4 - Ver as linhas. \n";
    std::cout << " 5 - Sair para o Menu.\n";
    std::cout << " Digite a sua opcao e presse ENTER: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
          createLine (lines);
        break;
        case 2:
          editLineMenu (lines, getLineIndex(lines));
        break;
        case 3:
          //removeLine (lines);
        break;
        case 4:
          //printLines (lines);
        break;
        case 5:
          changeState (state, Menu);
        break;
        default:
        break;
    }
}

void editLineMenu (std::vector<Line> &lines, unsigned int lineIndex){
    int choice;

    clearConsole();
    std::cout << "*******************************\n";
    std::cout << " 1 - ID.\n";
    std::cout << " 2 - Frequencia de circulacao.\n";
    std::cout << " 3 - Paragens.\n";
    std::cout << " 4 - Tempo entre Paragens.\n";
    std::cout << " 5 - Voltar.\n";
    std::cout << " Digite a sua opcao e presse ENTER: ";
    std::cin >> choice;
    //choice between 1 and 5

    switch (choice) {
        case 1:
          changeLineId (lines, lineIndex);
        break;
        case 2:
          //changeLineFreq (std::vector<Line> &lines, unsigned int lineIndex);
        break;
        case 3:
          //changeLineStops (std::vector<Line> &lines, unsigned int lineIndex);
        break;
        case 4:
          //changeLineTimeBetweenStops (std::vector<Line> &lines, unsigned int lineIndex);
        break;
        case 5:
          return;
        break;
        default:
        break;
    }
}
