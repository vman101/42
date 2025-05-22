/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:32:21 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/07 17:04:31 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <string>

Contact::Contact( void )
{
    std::cout << "Created contact" << std::endl;
}

Contact::~Contact( void )
{
    std::cout << "Deleted contact" << std::endl;
}

static bool    check_number(std::string number)
{
    for (unsigned int i = 0; i < number.length(); i++)
    {
        if (number[i] < '0' || number[i] > '9')
            return (false);
    }
    return (true);
}

static bool    check_alpha(std::string number)
{
    for (unsigned int i = 0; i < number.length(); i++)
    {
        if (!std::isalpha(number[i]))
            return (false);
    }
    return (true);
}

std::string get_number(std::string label)
{
    std::string input;
    std::cout << label << std::endl;
    while (std::getline(std::cin, input)) {
        if (!check_number(input) || input.empty()) {
            std::cout << "[ERROR] Expected not empty number" << std::endl;
        } else {
            return input;
        }
        std::cout << label << std::endl;
        input.clear();
    }
    return std::string("");
}

std::string get_input(std::string label)
{
    std::string input;
    std::cout << label << std::endl;
    while (std::getline(std::cin, input)) {
        if (!check_alpha(input) || input.empty()) {
            std::cout << "[ERROR] Expected not empty english alphabet" << std::endl;
        } else {
            return input;
        }
        std::cout << label << std::endl;
        input.clear();
    }
    return std::string("");
}

Contact Contact::DefineNew( void )
{
    Contact contact;

    while (1) {
        contact.first_name = get_input("Enter First Name:");
        if (contact.first_name.empty()) break;
        contact.last_name = get_input("Enter Last Name:");
        if (contact.last_name.empty()) break;
        contact.nick_name = get_input("Enter Nickname:");
        if (contact.nick_name.empty()) break;
        contact.phone_number = get_number("Enter Phonenumber:");
        if (contact.phone_number.empty()) break;
        contact.darkest_secret = get_input("Enter Darkest Secret:");
        if (contact.darkest_secret.empty()) break;
        return contact;
    }
    contact.first_name = "";

    return contact;
}

void    Contact::FirstNameSet(std::string first_name)
{
    this->first_name = first_name;
}

void    Contact::LastNameSet(std::string last_name)
{
    this->last_name = last_name;
}

void    Contact::NickNameSet(std::string nick_name)
{
    this->nick_name = nick_name;
}

std::string    Contact::FirstNameGet( void ) const
{
    return this->first_name;
}

std::string    Contact::LastNameGet( void ) const
{
    return this->last_name;
}

std::string    Contact::NickNameGet( void ) const
{
    return this->nick_name;
}

std::string    Contact::PrintFormat(std::string str)
{
    int len = str.length();
    std::string formatted;
    for (int i = 0; i < len; i++)
    {
        formatted.push_back(str[i]);
        if (i == 8)
        {
            formatted.push_back('.');
            break ;
        }
    }
    return formatted;
}

void Contact::Display( void )
{
    std::cout << "First Name: " << this->first_name << std::endl;
    std::cout << "Last Name: " << this->last_name << std::endl;
    std::cout << "Nickname: " << this->nick_name << std::endl;
    std::cout << "Phone Number: " << this->phone_number << std::endl;
    std::cout << "Darkest Secret: " << this->darkest_secret << std::endl;
}
