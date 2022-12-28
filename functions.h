#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include <ctime>

// If user inputs text instead of numbers, prints out error
void user_input_error(const std::string input);

// Separates a string using delimiter. Outputs vector, each element being a separate part of string.
// Default delimiter is comma.
std::vector<std::string> split_string(std::string str, const char delimiter = ',');

// Takes user input and converts to date of type string
struct std::tm get_date();

// Takes start date and end date of order. Prints date details to terminal
void show_date(const std::tm& start_date, const std::tm& end_date);

#endif