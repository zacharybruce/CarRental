#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <fstream>
#include "Car.h"
#include "functions.h"

Car::Car()
{
}
Car::Car(std::string_view type, std::string_view make, std::string_view model,
    int year, bool availability) :
    m_type(type), m_make(make), m_model(model), m_year(year), m_availability(availability)
{
}
Car::~Car()
{
}


// getters
std::string Car::get_type(){
    return m_type;
}
std::string Car::get_make(){
    return m_make;
}
std::string Car::get_model(){
    return m_model;
}
int Car::get_year(){
    return m_year;
}
bool Car::get_availability(){
    return m_availability;
}


// setters
void Car::set_type(std::string type){
    m_type = type;
}
void Car::set_make(std::string make){
    m_make = make;
}
void Car::set_model(std::string model){
    m_model = model;
}
void Car::set_year(int year){
    m_year = year;
}
void Car::set_availability(bool availability){
    m_availability = availability;
}


void Car::print_info(){
    std::cout << "\t" << m_make << ' ' << m_model << std::endl;
    std::cout << "\t" << "Year: " << m_year << std::endl;
    if (m_availability){
        std::cout << "\t" << "Available" << std::endl;
    }
    else{
        std::cout << "\t" << "Unavailable" << std::endl;
    }
    std::cout << std::endl;
}


void Car::show_details(Car& car, const std::string& path, const std::string& car_type){
    std::string line;
    std::ifstream file(path);
    std::vector<std::string> car_details;

    if (file.is_open()){
        while (std::getline(file, line)){
            car_details = split_string(line);
            car.set_type(car_type);
            car.set_make(car_details[0]);
            car.set_model(car_details[1]);
            car.set_year(std::stoi(car_details[2]));
            if (car_details[3] == "a"){
                car.set_availability(true);
            }
            else{
                car.set_availability(false);
            }
            car.print_info();
        }
    }
}

