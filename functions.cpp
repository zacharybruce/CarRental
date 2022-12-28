#include <iostream>
#include <ctime>
#include <string>
#include <unordered_map>
#include <limits>
#include "functions.h"

void user_input_error(const std::string input){
    std::cout << input << std::endl;
    std::cout << std::endl;
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}


std::vector<std::string> split_string(std::string str, const char delimiter){

    std::vector<std::string> vct;
    std::string sub_string;
    size_t pos {};

    // Pushes sub_string to vector when delimiter is reached
    while((pos = str.find(delimiter)) != std::string::npos){
        sub_string = str.substr(0,pos);
        vct.push_back(sub_string);
        str.erase(0, pos + 1);
    }
    vct.push_back(str);

    return vct;
}

struct std::tm get_date(){
    int month {};
    int day {};
    int year {};

    while ((month < 1) || (month > 12)){
        std::cout << "month (1-12): ";
        std::cin >> month;
        if (!std::cin){
            user_input_error("Please enter number 1-12");
        }
    }
    
    while ((day < 1) || (day > 31)){
        std::cout << "day (1-31): ";
        std::cin >> day;
        if (!std::cin){
            user_input_error("Please enter number 1-31");
        }
    }
    
    while (year <= 0){
        std::cout << "year: ";
        std::cin >> year; 
        if (!std::cin){
            user_input_error("Please enter valid year");
        }   
    }
    std::cout << std::endl;    

    // convert user input to date and time
    struct std::tm input_date = {0, 0, 0, day, month-1, year-1900};

    return input_date;
}


void show_date(const std::tm& start_date, const std::tm& end_date){
    // Maps number to month names
    std::unordered_map<int, std::string> months = {
        {0,"January"},
        {1,"February"},
        {2,"March"},
        {3,"April"},
        {4,"May"},
        {5,"June"},
        {6,"July"},
        {7,"August"},
        {8,"September"},
        {9,"October"},
        {10,"November"},
        {11,"December"}
    };

    std::cout << '\t' << months[start_date.tm_mon] << ' ' << start_date.tm_mday << ", " << 1900+start_date.tm_year << std::endl;
    std::cout << "\tTO" << std::endl;
    std::cout << '\t' << months[end_date.tm_mon] << ' ' << end_date.tm_mday << ", " << 1900+end_date.tm_year << std::endl;
    std::cout << std::endl;
}
