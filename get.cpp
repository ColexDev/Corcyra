#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>

extern std::string token;
extern std::vector<std::string> allEntries;

std::string get_date(std::string &par_line)
{
    std::string date;
    std::istringstream ss_line(par_line);
    std::getline(ss_line, date, ',');
    std::getline(ss_line, date, ',');
    std::getline(ss_line, date, ',');
    std::getline(ss_line, date, ',');
    std::getline(ss_line, date, ',');
    return date;
}

// RETURNS THE MONTH (1, 2, 3, ETC)
int get_month(std::string &par_line)
{
    std::string date = get_date(par_line);
    std::istringstream ss_token(date);
    std::getline(ss_token, token, '-' );
    return stoi(token);
}

// RETURNS THE AMOUNT, FLOAT (15.65)
float get_amount_line_float(std:: string &par_line)
{
    std::istringstream ss_line(par_line);
    std::string amount;
    std::getline(ss_line, amount, ',');
    std::getline(ss_line, amount, ',');
    std::getline(ss_line, amount, ',');
    std::istringstream ss_amount(amount);
    std::getline(ss_amount, amount, '$');
    std::getline(ss_amount, amount, '$');
    return stof(amount);
}
// REMOVE THIS AND MAKE 1 FUNCTION / TEMPLATE FOR BOTH TYPES
std::string get_amount_line_string(std:: string &par_line)
{
    std::istringstream ss_line(par_line);
    std::string amount;
    std::getline(ss_line, amount, ',');
    std::getline(ss_line, amount, ',');
    std::getline(ss_line, amount, ',');
    std::istringstream ss_amount(amount);
    std::getline(ss_amount, amount, '$');
    std::getline(ss_amount, amount, '$');
    return amount;
}

// Gets the Type (Expense/Income)
std::string get_type(std::string &par_line)
{
    std::string type;
    std::istringstream ss_line(par_line);
    std::getline(ss_line, type, ',');
    return type;
}

std::string get_category(std::string &par_line)
{
    std::string category;
    std::istringstream ss_line(par_line);
    std::getline(ss_line, category, ',');
    std::getline(ss_line, category, ',');
    return category;
}


std::string get_description(std::string &par_line)
{
    std::string description;
    std::istringstream ss_line(par_line);
    std::getline(ss_line, description, ',');
    std::getline(ss_line, description, ',');
    std::getline(ss_line, description, ',');
    std::getline(ss_line, description, ',');
    return description;
}

float get_amount_category(std::string par_category)
{
    float amount = 0.0;
    for (auto entry : allEntries) {
        if ((get_category(entry) == par_category) && (get_type(entry) == "Income")) {
            amount += get_amount_line_float(entry);
        } else if ((get_category(entry) == par_category) && (get_type(entry) == "Expense")) {
            amount -= get_amount_line_float(entry);
        }
    }
    return amount;
}

float get_amount_total(const int par_MONTH, const std::string par_TYPE, const std::string par_CATEGORY)
{
    std::fstream database("database.txt");
    std::string line;
    int date;
    float amount = 0;
    if (par_CATEGORY == "All") {
        while(std::getline(database, line)) {
            if (par_TYPE == get_type(line) && par_MONTH == get_month(line)) {
                amount += get_amount_line_float(line);
            }
        }
    } else {
        while(std::getline(database, line)) {
            if (par_TYPE == get_type(line) && par_MONTH == get_month(line) && par_CATEGORY == get_category(line)) {
            amount += get_amount_line_float(line);
            }
        }
    }

    std::string numAmount {std::to_string(amount)};
return amount;
}

// Get the date and time
std::string get_current_date()
{
    std::time_t _time;
    std::tm* timeinfo;
    char time[80];
    std::time(&_time); // get time -> store in address
    timeinfo = std::localtime(&_time); // address to struct rep
    std::strftime(time, 80 ,"%m-%d-%Y", timeinfo); // format time to `time`
    std::string __time(time); // convert char[] -> std::string
    return __time;
}
