#include <iostream>
#include "MainMenu.h"

int main(){
    
    std::cout << "\nWelcome to Rent-A-Car!\n" << std::endl;

    MainMenu menu;
    while (1){
        menu.show_menu();
    }
    
    return 0;
}