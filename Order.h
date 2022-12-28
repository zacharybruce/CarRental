#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <string_view>
#include <ctime>

class Order{
    public:
        Order();
        Order(std::string_view first_name, std::string_view last_name,
            std::string_view type, std::tm start_date, std::tm end_date, double price);
        ~Order();

        // getters
        std::string get_first_name();
        std::string get_last_name();
        std::string get_type();
        std::tm get_start_date();
        std::tm get_end_date();
        double get_price();

        // setters
        void set_first_name(std::string first_name);
        void set_last_name(std::string last_name);
        void set_type(std::string type);
        void set_start_date(std::tm start_date);
        void set_end_date(std::tm end_date);
        void set_price(double price);

        // Retrieve order info from user input
        void retrieve_order_name();
        void retrieve_order_type();
        void retrieve_order_dates();

        bool check_availability(std::string_view car_type); // Check if type of car is available
        bool check_dates(std::tm start_date, std::tm end_date); // Check if end date is later than start date

        double calculate_price(); // Calculates total price of order

        void make_order(); // Write order details to Orders.txt
        void show_order(); // Show order by first and last name
        void cancel_order(); // Cancel order by first and last name


    private:
        std::string m_first_name;
        std::string m_last_name;
        std::string m_type;
        struct std::tm m_start_date;
        struct std::tm m_end_date;
        double m_price;
};

#endif