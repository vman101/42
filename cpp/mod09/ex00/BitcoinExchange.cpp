/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:09:55 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/25 15:17:45 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstring>
#include <exception>
#include <fstream>
#include <cerrno>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <iomanip>

const char *BitcoinExchange::DbFileNotOpen::what() const throw() {
    return "Failed to open database file";
}

BitcoinExchange::ParseError::~ParseError() throw() {}

const char *BitcoinExchange::ParseError::what() const throw() {
    return this->message.c_str();
}

E_LEVEL BitcoinExchange::ParseError::getLevel( void ) {
    return this->level;
}

BitcoinExchange::ParseError::ParseError(std::string message, E_LEVEL level): message("[Parsing Error] " + message), level(level) {}
BitcoinExchange::ParseError::ParseError(std::string& message, E_LEVEL level): message("[Parsing Error] " + message), level(level) {}
BitcoinExchange::ParseError::ParseError(const char *message, E_LEVEL level): message(message), level(level) {}

bool isValidDate(unsigned int Y, unsigned int M, unsigned int D) {
   if (Y < 1900 || Y > 2100 || M < 1 || M > 12 || D < 1 || D > 31) {
       return false;
   }

   unsigned int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

   bool isLeap = (Y % 4 == 0 && Y % 100 != 0) || (Y % 400 == 0);
   if (isLeap && M == 2) {
       daysInMonth[1] = 29;
   }

   return D <= daysInMonth[M - 1];
}

std::string    printDate(unsigned int packed) {
    unsigned int year = packed / 10000;
    unsigned int month = (packed % 10000) / 100;
    unsigned int day = packed % 100;

    std::stringstream s;

    s << year << "-"
        << std::setfill('0') << std::setw(2) << month
        << "-"
        << std::setfill('0') << std::setw(2) << day;
    return s.str();
}

unsigned int hash(unsigned int Y, unsigned int M, unsigned int D) {
    return Y * 10000 + M * 100 + D;
}

std::pair<unsigned int, float> BitcoinExchange::parseLine(std::string& line, std::string &seperator, unsigned int seperator_len, unsigned int line_count) const {
    unsigned int Y = 0, M = 0, D = 0;
    float value = 50;
    std::stringstream s(line);
    char c = 0;
    std::stringstream error;

    if (line.empty()) {
        throw ParseError("Encountered empty line", E_INFO);
    }

    s >> Y;
    if (s.fail() || Y < 1000 || Y > 9999 || s.tellg() != FORMAT_YEAR_LEN) {
        error << "Invalid Year Format at line: '" << line << "':" << line_count << " value: " << Y;
        throw ParseError(error.str(), E_WARNING);
    }

    s >> c;
    if (s.fail() || c != '-') {
        error << "Expected Hyphon got '" << c << "' at line: '" << line << "':" << line_count << " value: " << c;
        throw ParseError(error.str(), E_WARNING);
    }

    s >> M;
    if (s.fail() || M < 1 || M > 12 || s.tellg() != FORMAT_MONTH_LEN) {
        error << "Invalid Month Format at line: '" << line << "':" << line_count << " value: " << M;
        throw ParseError(error.str(), E_WARNING);
    }

    s >> c;
    if (s.fail() || c != '-') {
        error << "Expected Hyphon got '" << c << "' at line: '" << line << "':" << line_count << " value: " << c;
        throw ParseError(error.str(), E_WARNING);
    }

    s >> D;
    if (s.fail() || D < 1 || D > 31 || s.tellg() != FORMAT_DAY_LEN) {
        error << "Invalid Day Format at line: '" << line << "':" << line_count << " value: " << D;
        throw ParseError(error.str(), E_WARNING);
    }

    if (s.str().compare(s.tellg(), seperator_len, seperator, 0, seperator_len) != 0) {
        error << "Invalid Seperator Format at line: '" << line << "':" << line_count << " " << s.str().substr(s.tellg(), seperator_len);
        throw ParseError(error.str(), E_WARNING);
    }

    s.ignore(seperator_len);

    s >> value;
    if (s.fail() || !s.eof()) {
        error << "Invalid value Format at line: '" << line << "':" << line_count << " value: " << value;
        throw ParseError(error.str(), E_WARNING);
    }

    if (!isValidDate(Y, M, D)) {
        error << "Invalid Date at line: '" << line << "':" << line_count << " date: " << Y << "-" << M << "-" << D;
        throw ParseError(error.str(), E_WARNING);
    }
    return std::pair<int, float>(hash(Y, M, D), value);
}

BitcoinExchange::BitcoinExchange() {
    std::ifstream db(DEFAULT_FILE_PATH);
    if (!db) {
        std::cerr << "Failed to open file" << std::endl;
        if (errno != 0) {
            std::cerr << "System message: " << std::strerror(errno) << std::endl;
        }
        throw DbFileNotOpen();
    }
    std::string linebuf;

    std::string seperator;
    unsigned int seperator_len = 0;

    if (!std::getline(db, linebuf)) {
        throw ;
    }

    if (linebuf.compare(COMMA_FORMAT_HEADER) == 0) {
        seperator = COMMA_FORMAT_SEPERATOR;
        seperator_len = COMMA_FORMAT_SEPERATOR_LEN;
    } else {
        std::stringstream error;
        error << "Invalid DB File header: " << linebuf;
        throw ParseError(error.str(), E_ERROR);
    }

    unsigned int line_count = 1;

        while (std::getline(db, linebuf)) {
            try {
                this->dbInsertEntry(parseLine(linebuf, seperator, seperator_len, ++line_count));
            } catch (ParseError &e) {
                if (e.getLevel() == E_ERROR)
                    throw;
                std::cout << e.what() << std::endl;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
}

void    BitcoinExchange::extractRates(std::ifstream &input) const {
    std::string linebuf;

    if (!std::getline(input, linebuf)) {
        throw ;
    }

    std::stringstream error;
    std::string seperator;
    unsigned int seperator_len = 0;
    unsigned int line_count = 0;

    if (linebuf.compare(BAR_FORMAT_HEADER) == 0) {
        seperator = BAR_FORMAT_SEPERATOR;
        seperator_len = BAR_FORMAT_SEPERATOR_LEN;
    } else {
        error << "Invalid DB File header: " << linebuf;
        throw ParseError(error.str(), E_ERROR);
    }

    while (std::getline(input, linebuf)) {
        std::stringstream error;
        try {
            std::pair<unsigned int, float> pair = this->parseLine(linebuf, seperator, seperator_len, ++line_count);
            float amount = pair.second;

            if (amount < 0) {
                error << "Invalid negative amount at line: '" << linebuf << "':" << line_count << " amount: " << amount;
                throw ParseError(error.str(), E_WARNING);
            }

            if (amount > 1000) {
                error << "Invalid too large amount at line: '" << linebuf << "':" << line_count << " amount: " << amount;
                throw ParseError(error.str(), E_WARNING);
            }
            float rate = this->lookupDB(pair.first);
            std::cout << printDate(pair.first) << " => " << amount << " = " << amount * rate << std::endl;
        } catch (ParseError &e) {
            if (e.getLevel() == E_ERROR)
                throw ;
            std::cout << e.what() << std::endl;
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void    BitcoinExchange::dbInsertEntry(std::pair<unsigned int, float> entry) {
    this->db.insert(entry);
}

float BitcoinExchange::lookupDB(unsigned int key) const {
    std::map<unsigned int, float>::const_iterator it = this->db.upper_bound(key);

    if (it != this->db.begin()) {
        --it;
        return it->second;
    }
    throw std::runtime_error("[Lookup Error] Date too early: " + printDate(key));
    return 0;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other): db(other.db) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other) {
        this->db = other.db;
    }
    return (*this);
}
