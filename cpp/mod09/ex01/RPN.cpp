/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:23:31 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/08 17:26:38 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cctype>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <climits>

RPN::ParseError::~ParseError() throw() {}

const char *RPN::ParseError::what() const throw() {
    return this->message.c_str();
}

E_LEVEL RPN::ParseError::getLevel( void ) {
    return this->level;
}

RPN::ParseError::ParseError(std::string message, E_LEVEL level): message("[Parsing Error] " + message), level(level) {}
RPN::ParseError::ParseError(std::string& message, E_LEVEL level): message("[Parsing Error] " + message), level(level) {}
RPN::ParseError::ParseError(const char *message, E_LEVEL level): message(message), level(level) {}


RPN::RPN() {}

RPN::RPN(std::stringstream &ss) {
    while (ss.peek() != EOF) {
        int num;
        char op;

        ss >> std::ws;
        if (std::isdigit(ss.peek())) {
            num = std::strtol(ss.str().c_str(), NULL, 10);
            if (errno == ERANGE)
                throw std::logic_error("[Logic Error] Too large value detected");
            ss >> num;
            this->stack.push(num);
        } else {
            ss.clear();
            ss >> op;
            if (ss.fail()) {
                throw ParseError(std::string("Invalid character"), E_ERROR);
            }
            this->doOp(static_cast< ::op >(op));
        }
        ss >> std::ws;
    }
    if (this->stack.size() > 1) {
        throw std::logic_error("[Logic Error] Too many values left in Stack");
    }
    std::cout << this->stack.top() << std::endl;
}

void    RPN::doOp(op op) {
    if (this->stack.size() < 2) {
        throw std::logic_error("[Logic Error] Not enough values in Stack");
    }
    int b = this->stack.top(); this->stack.pop();
    int a = this->stack.top(); this->stack.pop();
    long long res;

    switch (op) {
        case OP_PLUS:
            if (static_cast<long long>(a) + static_cast<long long>(b) > INT_MAX)
                throw std::logic_error("[Logic Error] Integer Overflow Detected");
            else if (static_cast<long long>(a) + static_cast<long long>(b) < INT_MIN)
                throw std::logic_error("[Logic Error] Integer Underflow Detected");
            res = a + b;
            break;
        case OP_MINUS:
            if (static_cast<long long>(a) - static_cast<long long>(b) > INT_MAX)
                throw std::logic_error("[Logic Error] Integer Overflow Detected");
            else if (static_cast<long long>(a) - static_cast<long long>(b) < INT_MIN)
                throw std::logic_error("[Logic Error] Integer Underflow Detected");
            res = a - b;
            break;
        case OP_MUL:
            if (static_cast<long long>(a) * static_cast<long long>(b) > INT_MAX)
                throw std::logic_error("[Logic Error] Integer Overflow Detected");
            else if (static_cast<long long>(a) * static_cast<long long>(b) < INT_MIN)
                throw std::logic_error("[Logic Error] Integer Underflow Detected");
            res = a * b;
            break;
        case OP_DIV:
            if (b == 0)
                throw std::logic_error("[Logic Error] Division by zero");
            if (static_cast<long long>(a) / static_cast<long long>(b) > INT_MAX)
                throw std::logic_error("[Logic Error] Integer Overflow Detected");
            else if (static_cast<long long>(a) / static_cast<long long>(b) < INT_MIN)
                throw std::logic_error("[Logic Error] Integer Underflow Detected");
            res = a / b;
            break;
        default:
            throw ParseError(std::string("Invalid character '") + static_cast<char>(op) + "'", E_ERROR);
    }

    this->stack.push(res);
}

RPN::~RPN() {}

RPN::RPN(const RPN& other): stack(other.stack) {}

RPN &RPN::operator=(const RPN& other) {
    if (this != &other) {
        this->stack = other.stack;
    }
    return (*this);
}
