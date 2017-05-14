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
    Company company = Company("Semprarrolar","condutores.txt","linhas.txt");
    int op=0;

    printf("\033c");
    while(1){
        op = printMenu(menu);
        switch(menu){
            case 0:
                //UPDATE AOS FICHEIROS TXT
                if(!op){
                    if(update_linhas)
                        company.updateLines();
                    if(update_condutores)
                         company.updateDrivers();
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
                        company.newLine(&update_linhas);
                        break;
                    case 2:
                        company.changeLine(&update_linhas);
                        break;
                    case 3:
                        if(company.removeLine(&update_linhas))
                            printf("\033c");
                        break;
                    case 4:
                        company.printLines();
                        break;
                }
                break;
            case 2:
                switch(op){
                    case 0:
                        menu = 0;
                        break;
                    case 1:
                        company.newDriver(&update_condutores);
                        break;
                    case 2:
                        company.changeDriver(&update_condutores);
                        break;
                    case 3:
                        company.removeDriver(&update_condutores);
                        break;
                    case 4:
                        company.printDrivers();
                        break;
                }
                break;
            case 3:
                switch(op){
                case 0:
                    menu = 0;
                    break;
                case 1:
                        company.generateShifts();
                    break;
                case 2:
                        company.resetLineShifts();
                    break;
                case 3:
                        company.resetDriverShifts();
                    break;
                }
                break;
            case 4:
                switch(op){
                    case 0:
                        menu = 0;
                        break;
                    case 1:
                        company.printSchedules();
                        break;
                    case 2:
                        company.searchTrip();
                        break;
                    case 3:
                        company.printShifts();
                }
                break;
            case 5:
                wait_for_enter();
                menu = 0;
                break;
            default:
                break;
        }
    }
    return 0;
}
