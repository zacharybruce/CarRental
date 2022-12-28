#include <iostream>
#include "MainMenu.h"
#include "Car.h"
#include "Order.h"
#include "functions.h"


MainMenu::MainMenu()
{
}
MainMenu::~MainMenu()
{
}

void MainMenu::show_menu(){
    int option {};
    Order order;

    while ((option < 1) || (option > 4)){
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "Rent a car:   1" << std::endl;
        std::cout << "See Order:    2" << std::endl;
        std::cout << "Cancel Order: 3" << std::endl;
        std::cout << "Browse Cars:  4" << std::endl;
        std::cout << "Exit:         5" << std::endl;
        std::cout << "Choose Option: ";
        std::cin >> option;

        if (option == 1){
            order.make_order();
        }
        else if (option == 2){
            order.show_order();
        }
        else if (option == 3){
            order.cancel_order();
        }
        else if (option == 4){
            browse_menu();
        }
        else if (option == 5){
            exit(0);
        }
        else if (!std::cin){
            user_input_error("Please enter number 1-5");
        }
        option = 0; // re-initialize to 0 to make while loop run again
    }
}


void MainMenu::browse_menu(){
    int option {};
    Car car;

    std::cout << "\nChoose Car Type" << std::endl;
    std::cout << "Compact:  1" << std::endl;
    std::cout << "Midsize:  2" << std::endl;
    std::cout << "Fullsize: 3" << std::endl;
    std::cout << "Back:     4" << std::endl;
    std::cout << "Choice: ";
    std::cin >> option;
    std::cout << std::endl;

    if (option == 1){
        std::cout << "Showing Compact Cars" << std::endl;
        std::cout << std::endl;
        car.show_details(car, "Cars/compactCars.txt", "Compact");
    }
    else if (option == 2){
        std::cout << "Showing Midsize Cars" << std::endl;
        std::cout << std::endl;
        car.show_details(car, "Cars/midsizeCars.txt", "Midsize");
    }
    else if (option == 3){
        std::cout << "Showing Fullsize Cars" << std::endl;
        std::cout << std::endl;
        car.show_details(car, "Cars/fullsizeCars.txt", "Midsize");
    }
    else if (option == 4){
        this->show_menu();
    }
    else if (!std::cin){
        user_input_error("Please enter number 1-4");
    }
    else{
        std::cout << "Invalid Input" << std::endl;
        std::cout << std::endl;
    }
}