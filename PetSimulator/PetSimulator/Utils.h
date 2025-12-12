#pragma once

#include <iostream>
#include <limits>
#include <random>

#define LOG(X) std::cout << X
#define LOG_LN(X) std::cout << X << std::endl
#define LOG_EMPTY_LN std::cout << std::endl

#define string std::string

// Input Below
#define INPUT_WITH_ERROR(INPUT_TEXT, INPUT_VAR, ERROR_MESSAGE)\
do\
{\
    LOG(INPUT_TEXT << " : ");\
    std::cin >> INPUT_VAR;\
    if (!std::cin.fail())\
    {\
        break;\
    }\
    std::cin.clear();\
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');\
    std::cerr << ERROR_MESSAGE << std::endl;\
}\
while (true);

#define INPUT(INPUT_TEXT, INPUT_VAR)\
INPUT_WITH_ERROR(INPUT_TEXT, INPUT_VAR, "Invalid input. Please try again!");