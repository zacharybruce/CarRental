#include <string>
#include <string_view>
#include <ctime>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdio>
#include <iomanip>

#include "Order.h"
#include "functions.h"

Order::Order()
{
}
Order::Order(std::string_view first_name, std::string_view last_name, std::string_view type,
    std::tm start_date, std::tm end_date, double price) :
        m_first_name(first_name), m_last_name(last_name), m_type(type),
        m_start_date(start_date), m_end_date(end_date), m_price(price)
{
}
Order::~Order()
{
}

// getters
std::string Order::get_first_name(){
    return m_first_name;
}
std::string Order::get_last_name(){
    return m_last_name;
}
std::string Order::get_type(){
    return m_type;
}
std::tm Order::get_start_date(){
    return m_start_date;
}
std::tm Order::get_end_date(){
    return m_end_date;
}
double Order::get_price(){
    return m_price;
}

// setters
void Order::set_first_name(std::string first_name){
    m_first_name = first_name;
}
void Order::set_last_name(std::string last_name){
    m_last_name = last_name;
}
void Order::set_type(std::string type){
    m_type = type;
}
void Order::set_start_date(std::tm start_date){
    m_start_date = start_date;
}
void Order::set_end_date(std::tm end_date){
    m_end_date = end_date;
}
void Order::set_price(double price){
    m_price = price;
}


bool Order::check_availability(std::string_view car_type){
    std::ifstream file;
    std::string line;
    std::vector<std::string> car_details;

    // Opens correct car type file
    if (car_type == "Compact"){
        file.open("Cars/compactCars.txt");
    }
    else if (car_type == "Midsize"){
        file.open("Cars/midsizeCars.txt");
    }
    else if (car_type == "Fullsize"){
        file.open("Cars/fullsizeCars.txt");
    }
    else{
        std::cout << "Could not check availability" << std::endl;
        return false;
    }

    // If one car is available, returns true
    if (file.is_open()){
        while (std::getline(file, line)){
            car_details = split_string(line);
            if (car_details[3] == "a"){
                return true;
            }
        }
    }
    
    std::cout << std::endl;
    std::cout << car_type << " car is not available" << std::endl;
    return false;
}


bool Order::check_dates(std::tm start_date, std::tm end_date){
    std::time_t today_time = std::time(0); // todays date
    std::tm* today_struct = std::localtime(&today_time); // convert date to tm

    // Sets time of today to 00:00:00
    std::tm today_date = {0, 0, 0, today_struct->tm_mday, today_struct->tm_mon, today_struct->tm_year};

    std::time_t today = std::mktime(&today_date);
    std::time_t start = std::mktime(&start_date);
    std::time_t end = std::mktime(&end_date);

    // Checks if start date is current date or later,
    // and if end date is after start date
    if ((std::difftime(start, today) >= 0) && std::difftime(end, start) >= 0){
        return true;
    }

    std::cout << "Invalid Date Entry" << std::endl;
    std::cout << std::endl;
    return false;
}


// Retrieve order details from user input
void Order::retrieve_order_name(){
    std::string first_name {};
    std::string last_name {};
    while (first_name == ""){
        std::cout << std::endl;
        std::cout << "Enter First Name: ";
        std::cin >> first_name;
    }
    this->set_first_name(first_name);
    while (last_name == ""){
        std::cout << std::endl;
        std::cout << "Enter Last Name: ";
        std::cin >> last_name;
    }
    this->set_last_name(last_name);
}
void Order::retrieve_order_type(){
    int type_of_car {};
    while (type_of_car < 1 || type_of_car > 4){
        std::cout << std::endl;
        std::cout << "Choose Type of Car:" << std::endl;
        std::cout << "Compact:  1" << std::endl;
        std::cout << "Midsize:  2" << std::endl;
        std::cout << "Fullsize: 3" << std::endl;
        std::cout << "Exit:     4" << std::endl;
        std::cout << "Enter Number: ";
        std::cin >> type_of_car;
        
        if (!std::cin){
            user_input_error("Please enter number 1-4");
        }
    }

    if (type_of_car == 1){
        this->set_type("Compact");
    }
    else if (type_of_car == 2){
        this->set_type("Midsize");
    }
    else if (type_of_car == 3){
        this->set_type("Fullsize");
    }
    else{
        exit(0);
    }
}
void Order::retrieve_order_dates(){
    std::tm start_date;
    std::tm end_date;

    std::cout << std::endl;
    std::cout << "Start Date:" << std::endl;
    start_date = get_date();
    this->set_start_date(start_date);

    std::cout << "End Date:" << std::endl;
    end_date = get_date();
    this->set_end_date(end_date);
}


double Order::calculate_price(){
    // Map of car type and price per day
    std::unordered_map<std::string,double> price_per_day = {
        {"Compact", 55.99},
        {"Midsize", 66.75},
        {"Fullsize", 71.10}
    };
    
    std::time_t start_dt = std::mktime(&this->m_start_date);
    std::time_t end_dt = std::mktime(&this->m_end_date);
    
    // Calculates time between start date and end date in days
    double total_days = std::difftime(end_dt, start_dt) / 60 / 60 / 24;
    
    if (total_days == 0){
        total_days = 1.00;
    }

    return price_per_day[this->m_type] * total_days; // Price per day times total days of order
}


// Outputs to Orders.txt. Data on one line is:
// first name, last name, type, start month, start day, start year, end month, end day, end year, price
void Order::make_order(){

    bool is_available = false;
    bool valid_dates = false;

    // Retrieves name, car type, dates from user
    retrieve_order_name();
    while (!is_available){
        retrieve_order_type();
        is_available = check_availability(this->get_type());
    }
    while (!valid_dates){
        retrieve_order_dates();
        valid_dates = check_dates(this->get_start_date(), this->get_end_date());
    }

    this->set_price(this->calculate_price());

    std::ofstream file("Orders/Orders.txt", std::ios::app); // Append order to end of file
    if (file.is_open()){
        // Outputs to Orders.txt with info separated by comma
        file << this->m_first_name << ',';
        file << this->m_last_name << ',';
        file << this->m_type << ',';
        file << this->m_start_date.tm_mon << ',' << this->m_start_date.tm_mday << ',' << this->m_start_date.tm_year << ',';
        file << this->m_end_date.tm_mon << ',' << this->m_end_date.tm_mday << ',' << this->m_end_date.tm_year << ',';
        file << std::setprecision(2) << std::fixed << this->m_price << std::endl;
    }

    std::cout << "\tThank You " << this->get_first_name() << ' ' << this->get_last_name() << std::endl;
    std::cout << std::endl;
    std::cout << "\tRenting " << this->get_type() << " car from\n";
    show_date(this->m_start_date, this->m_end_date);

    std::cout << "\tTotal Price: $" << std::setprecision(2) << std::fixed << this->get_price() << std::endl;
    std::cout << std::endl;
}


void Order::show_order(){
    // Clear order to avoid instance holding info from multiple orders
    this->set_first_name("");
    this->set_last_name("");
    this->set_type("");
    this->set_start_date({0,0,0,0,0,0});
    this->set_end_date({0,0,0,0,0,0});
    this->set_price(0.00);

    retrieve_order_name();

    std::string line;
    std::vector<std::string> order_details;
    std::tm order_start_date;
    std::tm order_end_date;
    std::ifstream file("Orders/Orders.txt");

    bool order_found = false;

    if (file.is_open()){
        while (std::getline(file, line)){
            order_details = split_string(line);

            // Only show order with same first and last name
            if ((order_details[0] == this->m_first_name) && (order_details[1] == this->m_last_name)){

                order_found = true;

                // Sets order start date using Orders.txt
                order_start_date = {
                    0, 0 ,0, std::stoi(order_details[4]), std::stoi(order_details[3]), std::stoi(order_details[5])
                };
                // Sets order end date using Orders.txt
                order_end_date = {
                    0, 0, 0, std::stoi(order_details[7]), std::stoi(order_details[6]), std::stoi(order_details[8])
                };
                
                std::cout << std::endl;
                std::cout << "\tOrder for: " << order_details[0] << ' ' << order_details[1] << std::endl;
                std::cout << std::endl;
                std::cout << "\tRenting " << order_details[2] << " car from:" << std::endl;
                show_date(order_start_date, order_end_date);
                
                std::cout << "\tTotal Price: $" << order_details[9] << std::endl;
                std::cout << std::endl;
            }
        }
    }

    if (!order_found){
        std::cout << std::endl;
        std::cout << "\tOrder Not Found" << std::endl;
        std::cout << std::endl;
    }
}


// Creates new file called OrdersNew.txt
// Will contain all orders under different name
// than that supplied to by the user.
// OrdersNew.txt will then replace Orders.txt
void Order::cancel_order(){

    // Clear order to avoid instance holding info from multiple orders
    this->set_first_name("");
    this->set_last_name("");
    this->set_type("");
    this->set_start_date({0,0,0,0,0,0});
    this->set_end_date({0,0,0,0,0,0});
    this->set_price(0.00);

    std::ifstream filein("Orders/Orders.txt");
    std::ofstream fileout("Orders/OrdersNew.txt"); // Temporary name. Will replace
                                                   // Orders.txt
    std::string line;
    std::vector<std::string> order_details;
    bool order_found = false;

    retrieve_order_name();

    // Only transfer names not equal to name given by user
    if (filein.is_open() && fileout.is_open()){
        while (std::getline(filein, line)){
            order_details = split_string(line);
            if ((order_details[0] != this->m_first_name) || (order_details[1] != this->m_last_name)){
                fileout << line + '\n';
            }
            else{
                std::cout << std::endl;
                std::cout << "\tOrder Found" << std::endl;
                order_found = true;
            }
        }
    }
    
    std::remove("Orders/Orders.txt"); // Removes original file

    // Renames file to Orders.txt.
    // File contains orders with canceled order removed
    std::rename("Orders/OrdersNew.txt", "Orders/Orders.txt");

    if (order_found){
        std::cout << "\tOrder Canceled" << std::endl;
        std::cout << std::endl;
    }
    else{
        std::cout << std::endl;
        std::cout << "\tOrder Not Found" << std::endl;
        std::cout << std::endl;
    }
}
