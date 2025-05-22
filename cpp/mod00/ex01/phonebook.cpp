/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:02:34 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/07 17:01:44 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "phonebook.hpp"
#include    <cstdlib>
#include    <iomanip>
#include    <iostream>

Phonebook::Phonebook( void )
{
    std::locale::global(std::locale("en_US.UTF-8"));
    std::cout << "Created New Phonebook!" << std::endl;
    this->contact_cursor = 0;
    this->contact_count = 0;
}

Phonebook::~Phonebook()
{
    std::cout << "Deleted Phonebook" << std::endl;
}

void    Phonebook::Add( void )
{
    Contact newcontact = Contact::DefineNew();
    if (newcontact.FirstNameGet().empty())
        return ;
    this->contact[this->contact_cursor % MAX_CONTACT] = newcontact;
    this->contact_cursor++;
    this->contact_cursor %= MAX_CONTACT;
    if (this->contact_count < MAX_CONTACT)
        this->contact_count++;
    std::cout << "Adding Contact" << std::endl;
}

void    Phonebook::Display( void )
{
    std::cout << "Phonebook entries:" << std::endl;
    for (int i = 0; i < this->contact_count; i++) {
        std::cout << i << " |";
        std::cout << std::setw(10) << std::right << this->contact[i].PrintFormat(this->contact[i].FirstNameGet()) << "|";
        std::cout << std::setw(10) << std::right << this->contact[i].PrintFormat(this->contact[i].LastNameGet()) << "|";
        std::cout << std::setw(10) << std::right << this->contact[i].PrintFormat(this->contact[i].NickNameGet()) << std::endl;
    }
}

int    is_space(char const c)
{
    if ((c >= 9 && c <= 13) || c == ' ')
        return (1);
    return (0);
}

int    ft_atoi(char const *s)
{
    int            nb;
    char const    *tmp;

    nb = 0;
    while (is_space(*s))
        s++;
    tmp = s;
    if (*tmp == '+' || *tmp == '-')
        tmp++;
    while (*tmp >= '0' && *tmp <= '9')
    {
        nb *= 10;
        nb += (*tmp - '0');
        tmp++;
    }
    if (*s == '-')
        nb = -nb;
    return (nb);
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

void    Phonebook::Search( void )
{
    std::string    index;

    if (this->contact_count > 0)
    {
        this->Display();
        while (index.empty() || index.length() > 1 || (index[0] < '0' && index[1] > '9'))
        {
            std::cout << "Enter index: " << std::endl;
            std::getline(std::cin, index);
            if (std::cin.eof())
                return ;
            if (check_number(index)) {
                int index_num = ft_atoi(index.c_str());

                if (index_num >= 0 && index_num < 8 && index_num < this->contact_count) {
                    this->contact[index_num].Display();
                    break ;
                } else {
                    std::cout << "[ERROR] Contact not found!" << std::endl;
                }
            } else {
                std::cout << "[ERROR] Invalid input" << std::endl;
            }
            index.clear();
        }
    } else {
        std::cout << "[ERROR] You have no contacts, rip" << std::endl;
    }
}
