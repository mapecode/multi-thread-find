#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include <string>
#include <termcolor/termcolor.hpp>

#define MAX_CHAR    1024

/*** Color Constants ***/
#define RED         1
#define GREEN       2
#define YELLOW      3
#define BLUE        4
#define MAGENTA     5
#define CYAN        6
#define WHITE       7
#define N_COLORS    7

/*** Structs ***/
struct WordFinded
{
    int line;
    std::string word_;
    std::string predecessor;
    std::string successor;
};

/*** Shared functions ***/
void upper_to_lower(std::string &upper_string)
{
    std::transform(upper_string.begin(), upper_string.end(), upper_string.begin(), ::tolower);
}

/** Color functions **/
void print_red(std::string str)
{
    std::cout << termcolor::red << str << std::endl;
}

void print_green(std::string str)
{
    std::cout << termcolor::bold << termcolor::green << str << std::endl;
}

void print_yellow(std::string str)
{
    std::cout << termcolor::bold << termcolor::yellow << str << std::endl;
}

void print_blue(std::string str)
{
    std::cout << termcolor::bold << termcolor::blue << str << std::endl;
}

void print_magenta(std::string str)
{
    std::cout << termcolor::bold << termcolor::magenta << str << std::endl;
}

void print_cyan(std::string str)
{
    std::cout << termcolor::bold << termcolor::cyan << str << std::endl;
}

void print_white(std::string str)
{
    std::cout << termcolor::bold << termcolor::white << str << std::endl;
}

void reset_color()
{
    std::cout << termcolor::reset << std::endl;
}

#endif


