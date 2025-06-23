/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:48:29 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/23 16:17:20 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include "utils.hpp"
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>

const char *ScalarConverter::EmptyInput::what() const throw() {
    return "Empty input";
}

const char *ScalarConverter::InvalidInput::what() const throw() {
    return "Invalid input format";
}

const char *ScalarConverter::FloatInfPositive::what() const throw() {
    return "+inff";
}

const char *ScalarConverter::FloatInfNegative::what() const throw() {
    return "-inff";
}

const char *ScalarConverter::FloatNAN::what() const throw() {
    return "nanf";
}

const char *ScalarConverter::DoubleInfPositive::what() const throw() {
    return "+inf";
}

const char *ScalarConverter::DoubleInfNegative::what() const throw() {
    return "-inf";
}

const char *ScalarConverter::DoubleNAN::what() const throw() {
    return "nan";
}

const char *ScalarConverter::NoDisplay::what() const throw() {
    return "Cant display for this type";
}

const char *ScalarConverter::ImpossibleConversion::what() const throw() {
    return "impossible conversion";
}



ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }

ScalarConverter &ScalarConverter::operator=(const ScalarConverter& other) {
    (void)other;
    return (*this);
}

bool    ScalarConverter::is_pseudo(std::string& input) {
    if (input == "nanf" || input == "nan") {
        this->type = T_NAN;
        return true;
    } else if (input == "+inff" || input == "+inf") {
        this->type = T_INFP;
        return true;
    } else if (input == "-inff" || input == "-inf") {
        this->type = T_INFN;
        return true;
    }
    return false;
}

void ScalarConverter::is_valid(std::string& input) {
    trim_inplace(input);

    bool period = false;

    if (input.length() == 1) {
        return ;
    }

    for (uint i = 0; i < input.length(); i++) {
        if (!std::isdigit(input[i])) {
            if (i == 0 && (input[i] == '+' || input[i] == '-')) {
                continue;
            } else if (input[i] == '.' && period == false) {
                period = true;
            } else if (i + 1 == input.length() && input[i] == 'f') {
                continue;
            } else {
                throw ScalarConverter::InvalidInput();
            }
        }
    }

    return ;
}

void ScalarConverter::detect_type(std::string& input) {
    bool period = false;
    t_type type;

    if (this->is_pseudo(input)) {
        return ;
    }

    this->is_valid(input);

    uint len = input.length();

    if (len == 1 && !std::isdigit(input[0])) {
        type = T_CHAR;
    } else {
        type = T_INT;
    }

    for (uint i = 0; i < len; i++) {
        if (input[i] == '.') {
            if (period == false && len > 1) {
                type = T_DOUBLE;
                period = true;
            } else {
                throw ScalarConverter::InvalidInput();
            }
        }
    }

    if (input[len - (len > 0)] == 'f') {
        if (period == false) {
            throw ScalarConverter::InvalidInput();
        } else {
            type = T_FLOAT;
        }
    }

    if (period == false && len > INTMAX_SIZE)
        type = T_DOUBLE;
    this->type = type;

    char *endptr = NULL;
    switch (type) {
        case T_CHAR:
            this->c = static_cast<char>(input[0]);
            break ;
        case T_INT:
            this->i = std::atoi(input.c_str());
            break ;
        case T_FLOAT:
            this->f = std::atof(input.c_str());
            break ;
        case T_DOUBLE:
            this->d = std::strtod(input.c_str(), &endptr);
            break ;
        default:
            break;
    }
}

void    ScalarConverter::conv_char(void) {
    std::cout << "char: ";
    try {
        char c = this->get_char();
        if (!std::isprint(c)) {
            throw ScalarConverter::NoDisplay();
        }
        std::cout << "'" << c << "'";
    } catch ( std::exception &e ) {
        std::cout << e.what();
    }
    std::cout << std::endl;
}

void    ScalarConverter::conv_int() {
    std::cout << "int: ";
    try {
        std::cout << this->get_int();
    } catch ( std::exception &e ) {
        std::cout << e.what();
    }
    std::cout << std::endl;
}

void    ScalarConverter::conv_float(void) {
    std::cout << "float: ";
    try {
        std::cout << std::fixed << std::setprecision(1) << this->get_float();
    } catch ( std::exception &e ) {
        std::cout << e.what();
    }
    std::cout << std::endl;
}

void    ScalarConverter::conv_double(void) {
    std::cout << "double: ";
    try {
        std::cout << std::fixed << std::setprecision(1) << this->get_double();
    } catch ( std::exception &e ) {
        std::cout << e.what();
    }
    std::cout << std::endl;
}

char ScalarConverter::get_char( void ) {
    switch (this->type) {
        case T_CHAR:
            if (this->c < 0) {
                throw ScalarConverter::ImpossibleConversion();
            }
            return this->c;
        case T_INT:
            if (this->i < 0) {
                throw ScalarConverter::ImpossibleConversion();
            }
            return static_cast<char>(this->i);
        case T_FLOAT:
            if (this->f > CHAR_MAX || this->f < CHAR_MIN) {
                throw ScalarConverter::ImpossibleConversion();
            }
            return static_cast<char>(this->f);
        case T_DOUBLE:
            if (this->d > CHAR_MAX || this->d < CHAR_MIN) {
                throw ScalarConverter::ImpossibleConversion();
            }
            return static_cast<char>(this->d);
        case T_INFP:
        case T_INFN:
        case T_NAN:
            throw ScalarConverter::ImpossibleConversion();
    }
}

float ScalarConverter::get_float( void ) {
    switch (this->type) {
        case T_CHAR:
            return static_cast<float>(this->c);
        case T_INT:
            return static_cast<float>(this->i);
        case T_FLOAT:
            return this->f;
        case T_DOUBLE:
            return static_cast<float>(this->d);
        case T_INFP:
            throw ScalarConverter::FloatInfPositive();
        case T_INFN:
            throw ScalarConverter::FloatInfNegative();
        case T_NAN:
            throw ScalarConverter::FloatNAN();
    }
}

double ScalarConverter::get_double( void ) {
    switch (this->type) {
        case T_CHAR:
            return static_cast<double>(this->c);
        case T_INT:
            return static_cast<double>(this->i);
        case T_FLOAT:
            return static_cast<double>(this->f);
        case T_DOUBLE:
            return this->d;
        case T_INFP:
            throw ScalarConverter::DoubleInfPositive();
        case T_INFN:
            throw ScalarConverter::DoubleInfNegative();
        case T_NAN:
            throw ScalarConverter::DoubleNAN();
    }
}

int ScalarConverter::get_int( void ) {
    switch (this->type) {
        case T_CHAR:
            return static_cast<int>(this->c);
        case T_INT:
            return this->i;
        case T_FLOAT:
            if (this->f > static_cast<float>(INT_MAX) || this->f < static_cast<float>(INT_MIN)) {
                throw ScalarConverter::ImpossibleConversion();
            }
            return static_cast<int>(this->f);
        case T_DOUBLE:
            if (this->d > INT_MAX || this->d < INT_MIN) {
                throw ScalarConverter::ImpossibleConversion();
            }
            return static_cast<int>(this->d);
        case T_INFP:
        case T_INFN:
        case T_NAN:
            throw ScalarConverter::ImpossibleConversion();
    }
}

void    ScalarConverter::convert(const std::string &input) {
    std::string using_input;
    if (input.length() == 0) {
        throw ScalarConverter::EmptyInput();
    }
    ScalarConverter c;
    using_input = input;
    c.detect_type(using_input);
    c.conv_char();
    c.conv_int();
    c.conv_float();
    c.conv_double();
}
