#include <iostream>

#include "semprarrolar.h"
#include "menu.h"

void mainMenu (appState &state){
  unsigned int choice;

  clearConsole();
  std::cout << "*******************************\n";
  std::cout << " 1 - Gestao de linhas.\n";
  std::cout << " 2 - Gestao de condutores.\n";
  std::cout << " 3 - Visualizacao de informacao.\n";
  std::cout << " 4 - Sair.\n";
  do{
    nextUnsignedInt ("Digite a sua opcao e presse ENTER: ", choice);
  }while (choice>4 || choice<1);

  switch (choice) {
    case 1:
    {
      changeState (state, ManageLines);
    }
    break;

    case 2:
    {
      changeState (state, ManageDrivers);
    }
    break;

    case 3:
    {
      changeState (state, ViewInf);
    }
    break;

    case 4:
    {
      changeState (state, Quit);
    }
    break;

    default:
    break;
  }
}

void manageLineMenu (appState &state, std::vector<Line> &lines){
  unsigned int choice;

  sortLines (lines);
  clearConsole();

  std::cout << "*******************************\n";
  std::cout << " 1 - Criar uma linha.\n";
  std::cout << " 2 - Editar uma linha.\n";
  std::cout << " 3 - Remover uma linha.\n";
  std::cout << " 4 - Ver as linhas.\n";
  std::cout << " 5 - Guardar as linhas.\n";
  std::cout << " 6 - Sair para o Menu.\n";
  do{
    nextUnsignedInt ("Digite a sua opcao e presse ENTER: ", choice);
  }while (choice>6 || choice<1);

  switch (choice) {
    case 1:
    {
      createLine (lines);
    }
    break;

    case 2:
    {
      editLineMenu (lines, getLineIndex(lines));
    }
    break;

    case 3:
    {
      removeLine (lines, getLineIndex(lines));
    }
    break;

    case 4:
    {
      printLines (lines);
    }
    break;

    case 5:
    {
      storeLines (askFilePath(), lines);
    }
    break;

    case 6:
    {
      changeState (state, Menu);
    }
    break;

    default:
    break;
  }
}

void editLineMenu (std::vector<Line> &lines, unsigned int lineIndex){
  unsigned int choice;

  clearConsole();
  std::cout << "*******************************\n";
  std::cout << " 1 - ID.\n";
  std::cout << " 2 - Frequencia de circulacao.\n";
  std::cout << " 3 - Paragens.\n";
  std::cout << " 4 - Tempo entre Paragens.\n";
  std::cout << " 5 - Voltar.\n";
  do{
    nextUnsignedInt ("Digite a sua opcao e presse ENTER: ", choice);
  }while (choice>5 || choice<1);

  switch (choice) {
    case 1:
    {
      changeLineId (lines, lineIndex);
    }
    break;

    case 2:
    {
      changeLineFreq (lines.at(lineIndex));
    }
    break;

    case 3:
    {
      changeLineStopsMenu (lines.at(lineIndex));
    }
    break;

    case 4:
    {
      changeLineTimeBetweenStopsMenu (lines.at(lineIndex));
    }
    break;

    case 5:
    {
      return;
    }
    break;

    default:
    break;
  }
}

void changeLineStopsMenu (Line &line){
  unsigned int choice;

  clearConsole();
  std::cout << "*******************************\n";
  std::cout << " 1 - Adicionar Paragem.\n";
  std::cout << " 2 - Remover Paragem.\n";
  std::cout << " 3 - Voltar.\n";
  do{
    nextUnsignedInt ("Digite a sua opcao e presse ENTER: ", choice);
  }while (choice>3 || choice<1);

  switch (choice) {
    case 1:
    {
      addLineStopMenu (line);
    }
    break;

    case 2:
    {
      removeLineStopMenu (line);
    }
    break;

    case 3:
    {
      return;
    }
    break;

    default:
    break;
  }
}

void changeLineTimeBetweenStopsMenu (Line &line){
  std::vector<std::string> stops = line.getStops();
  std::vector<unsigned int> timeBetweenStops = line.getTimeBetweenStops();
  unsigned int choice;

  clearConsole();

  for (unsigned int i=0; i<timeBetweenStops.size(); i++){
    std::cout << i+1 << " - Entre ";
    std::cout << stops.at(i) << " e " << stops.at(i+1) <<std::endl;
  }
  do{
    nextUnsignedInt ("Digite a sua opcao e presse ENTER: ", choice);
  }while (choice>(timeBetweenStops.size()) || choice<1);

  line.changeTimeBetweenStops (choice-1);
}

void addLineStopMenu (Line &line){
  std::vector<std::string> stops = line.getStops();
  unsigned int choice, i;

  clearConsole();

  std::cout << "1 - No inicio da linha\n";
  for (i=0; i<(stops.size()-1); i++){
    std::cout << i+2 << " - Entre ";
    std::cout << stops.at(i) << " e " << stops.at(i+1) << std::endl;
  }
  std::cout << i+2 << " - No fim da linha\n";

  do{
    nextUnsignedInt ("Digite a sua opcao e presse ENTER: ", choice);
  }while (choice>(stops.size()+1) || choice<1); //(stops.size()+1) because we can add at the end of the line

  line.addStop (choice-1);
}

void removeLineStopMenu (Line &line){
  std::vector<std::string> stops = line.getStops();
  unsigned int choice;

  clearConsole();

  for (unsigned int i=0; i<(stops.size()); i++){
    std::cout << i+1 << " - "<<  stops.at(i) << std::endl;
  }

  do{
    nextUnsignedInt ("Digite a sua opcao e presse ENTER: ", choice);
  }while (choice>stops.size() || choice<1);
  line.removeStop (choice-1);
}

void manageDriverMenu (appState &state, std::vector<Driver> &drivers){
  unsigned int choice;

  sortDrivers (drivers);
  clearConsole();
  std::cout << "*******************************\n";
  std::cout << " 1 - Criar um condutor.\n";
  std::cout << " 2 - Editar um condutor.\n";
  std::cout << " 3 - Remover um condutor.\n";
  std::cout << " 4 - Ver os condutores. \n";
  std::cout << " 5 - Guardar os condutores. \n";
  std::cout << " 6 - Sair para o Menu.\n";
  do{
    nextUnsignedInt ("Digite a sua opcao e presse ENTER: ", choice);
  }while (choice>6 || choice<1);

  switch (choice) {
    case 1:
    {
      createDriver (drivers);
    }
    break;

    case 2:
    {
      editDriverMenu (drivers, getDriverIndex(drivers));
    }
    break;

    case 3:
    {
      removeDriver (drivers, getDriverIndex(drivers));
    }
    break;

    case 4:
    {
      printDrivers (drivers);
    }
    break;

    case 5:
    {
      storeDrivers (askFilePath(), drivers);
    }
    break;

    case 6:
    {
      changeState (state, Menu);
    }
    break;

    default:
    break;
  }
}

void editDriverMenu (std::vector<Driver> &drivers, unsigned int driverIndex){
  unsigned int choice;

  clearConsole();
  std::cout << "*******************************\n";
  std::cout << " 1 - ID.\n";
  std::cout << " 2 - Nome.\n";
  std::cout << " 3 - Maximo de horas por turno.\n";
  std::cout << " 4 - Maximo de horas por semana. \n";
  std::cout << " 5 - Minimo de horas por descanso. \n";
  std::cout << " 6 - Voltar.\n";
  do{
    nextUnsignedInt ("Digite a sua opcao e presse ENTER: ", choice);
  }while (choice>6 || choice<1);

  switch (choice) {
    case 1:
    {
      changeDriverId (drivers, driverIndex);
    }
    break;

    case 2:
    {
      changeDriverName (drivers.at(driverIndex));
    }
    break;

    case 3:
    {
      changeDriverMaxShiftHours (drivers.at(driverIndex));
    }
    break;

    case 4:
    {
      changeDriverMaxWeekHours (drivers.at(driverIndex));
    }
    break;

    case 5:
    {
      changeDriverMinBetweenShiftHours (drivers.at(driverIndex));
    }
    break;

    case 6:
    {
      return;
    }
    break;

    default:
    break;
  }
}


void viewInfMenu (appState &state, std::vector<Line> &lines, std::vector<Driver> &drivers){
  unsigned int choice;

  clearConsole();
  std::cout << "*******************************\n";
  std::cout << " 1 - Horarios.\n";
  std::cout << " 2 - Linhas.\n";
  std::cout << " 3 - Percursos.\n";
  std::cout << " 4 - Voltar.\n";
  do{
    nextUnsignedInt ("Digite a sua opcao e presse ENTER: ", choice);
  }while (choice>4 || choice<1);

  switch (choice) {
    case 1:
    {
      stopTimeTable (getStop(lines), lines);
    }
    break;

    case 2:
    {
      lineTimeTable (lines.at(getLineIndex(lines)));
    }
    break;

    case 3:
    {
      routeTimeTable (lines);
    }
    break;

    case 4:
    {
      changeState (state, Menu);
    }
    break;

    default:
    break;
  }
}
