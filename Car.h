#ifndef CAR_H
#define CAR_H

#include <string>
#include <string_view>

class Car{
    public:
        Car();
        Car(std::string_view type, std::string_view make, std::string_view model,
            int year, bool availability);
        ~Car();

        // getters
        std::string get_type();
        std::string get_make();
        std::string get_model();
        int get_year();
        bool get_availability();

        // setters
        void set_type(std::string type);
        void set_make(std::string make);
        void set_model(std::string model);
        void set_year(int year);
        void set_availability(bool availability);

        void print_info(); // Prints car details to terminal
        void show_details(Car& car, const std::string& path, const std::string& car_type); // Gets car info from text file

    private:
        std::string m_type; // Type of car (compact, midsize, fullsize, etc...)
        std::string m_make; // Make of car (Ford, Chevrolet...)
        std::string m_model; // Model of car (Focus, Bolt...)
        int m_year;
        bool m_availability; // Is car available
};

#endif