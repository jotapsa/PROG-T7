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
    nextInt (" Digite a sua opcao e presse ENTER: ", choice);

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
    std::cout << " 4 - Ver as linhas.\n";
    std::cout << " 5 - Guardar as linhas.\n";
    std::cout << " 6 - Sair para o Menu.\n";
    nextInt (" Digite a sua opcao e presse ENTER: ", choice);

    switch (choice) {
        case 1:
          createLine (lines);
        break;
        case 2:
          editLineMenu (lines, getLineIndex(lines));
        break;
        case 3:
          removeLine (lines, getLineIndex(lines));
        break;
        case 4:
          printLines (lines);
        break;
        case 5:
          storeLines (askFilePath(), lines);
        break;
        case 6:
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
    nextInt (" Digite a sua opcao e presse ENTER: ", choice);
    //choice between 1 and 5

    switch (choice) {
        case 1:
          changeLineId (lines, lineIndex);
        break;
        case 2:
          changeLineFreq (lines, lineIndex);
        break;
        case 3:
          changeLineStopsMenu (lines, lineIndex);
        break;
        case 4:
          changeLineTimeBetweenStops (lines, lineIndex);
        break;
        case 5:
          return;
        break;
        default:
        break;
    }
}

void changeLineStopsMenu (std::vector<Line> &lines, unsigned int lineIndex){
  int choice;

  clearConsole();
  std::cout << "*******************************\n";
  std::cout << " 1 - Adicionar Paragem.\n";
  std::cout << " 2 - Remover Paragem.\n";
  std::cout << " 3 - Voltar.\n";
  nextInt (" Digite a sua opcao e presse ENTER: ", choice);
  //choice between 1 and 3

  switch (choice) {
      case 1:
        addLineStopMenu (lines, lineIndex);
      break;
      case 2:
        removeLineStopMenu (lines, lineIndex);
      break;
      case 3:
        return;
      break;
      default:
      break;
  }
}

void addLineStopMenu (std::vector<Line> &lines, unsigned int lineIndex){
  std::vector<std::string> stops = lines.at(lineIndex).getStops();
  unsigned int pos, i;

  clearConsole();

  std::cout << "1 - No inicio da linha\n";
  for (i=0; i<(stops.size()-1); i++){
    std::cout << i+2 << " - Entre ";
    std::cout << stops.at(i) << " e " << stops.at(i+1) << std::endl;
  }
  std::cout << i+2 << " - No fim da linha\n";
  //falta validar que a opcao esta entre 1 e stops.size()
  nextUnsignedInt (" Digite a sua opcao e presse ENTER: ", pos);

  lines.at(lineIndex).addStop (pos-1);
}

void removeLineStopMenu (std::vector<Line> &lines, unsigned int lineIndex){
  std::vector<std::string> stops = lines.at(lineIndex).getStops();
  unsigned int pos;
  clearConsole();

  for (unsigned int i=0; i<(stops.size()); i++){
    std::cout << i+1 << " - "<<  stops.at(i) << std::endl;
  }

  //falta validar que a opcao esta entre 1 e stops.size()
  nextUnsignedInt (" Digite a sua opcao e presse ENTER: ", pos);
  lines.at(lineIndex).removeStop (pos-1);
}

void manageDriverMenu (appState &state, std::vector<Driver> &drivers){
    int choice;

    clearConsole();
    std::cout << "*******************************\n";
    std::cout << " 1 - Criar um condutor.\n";
    std::cout << " 2 - Editar um condutor.\n";
    std::cout << " 3 - Remover um condutor.\n";
    std::cout << " 4 - Ver os condutores. \n";
    std::cout << " 5 - Guardar os condutores. \n";
    std::cout << " 6 - Sair para o Menu.\n";
    nextInt (" Digite a sua opcao e presse ENTER: ", choice);

    switch (choice) {
        case 1:
          createDriver (drivers);
        break;
        case 2:
          editDriverMenu (drivers, getDriverIndex(drivers));
        break;
        case 3:
          removeDriver (drivers, getDriverIndex(drivers));
        break;
        case 4:
          printDrivers (drivers);
        break;
        case 5:
          storeDrivers (askFilePath(), drivers);
        break;
        case 6:
          changeState (state, Menu);
        break;
        default:
        break;
    }
}

void editDriverMenu (std::vector<Driver> &drivers, unsigned int driverIndex){
  int choice;

  clearConsole();
  std::cout << "*******************************\n";
  std::cout << " 1 - ID.\n";
  std::cout << " 2 - Nome.\n";
  std::cout << " 3 - Maximo de horas por turno.\n";
  std::cout << " 4 - Maximo de horas por semana. \n";
  std::cout << " 5 - Minimo de horas por descanso. \n";
  std::cout << " 6 - Voltar.\n";
  nextInt (" Digite a sua opcao e presse ENTER: ", choice);

  switch (choice) {
      case 1:
        changeDriverId (drivers, driverIndex);
      break;
      case 2:
        changeDriverName (drivers, driverIndex);
      break;
      case 3:
        changeDriverMaxShiftHours (drivers, driverIndex);
      break;
      case 4:
        changeDriverMaxWeekHours (drivers, driverIndex);
      break;
      case 5:
        changeDriverMinBetweenShiftHours (drivers, driverIndex);
      break;
      case 6:
        return;
      break;
      default:
      break;
  }
}


void viewInfMenu (appState &state, std::vector<Line> &lines, std::vector<Driver> &drivers){
  int choice;

  clearConsole();
  std::cout << "*******************************\n";
  std::cout << " 1 - Horarios.\n";
  std::cout << " 2 - Linhas.\n";
  std::cout << " 3 - Percursos.\n";
  std::cout << " 4 - Voltar.\n";
  nextInt (" Digite a sua opcao e presse ENTER: ", choice);

  switch (choice) {
      case 1:
        stopTimeTable (getStop(lines), lines);
      break;
      case 2:
        lineTimeTable (lines.at(getLineIndex(lines)));
      break;
      case 3:
        //changeDriverMaxShiftHours (drivers, driverIndex);
      break;
      case 4:
        changeState (state, Menu);
      break;
      default:
      break;
  }
}
