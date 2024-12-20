/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:32:21 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 19:32:13 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"
#include <iostream>

Contact::Contact( void )
{
	std::cout << "Created contact" << std::endl;
}

Contact::~Contact( void )
{
}

bool	check_number(std::string number)
{
	for (unsigned int i = 0; i < number.length(); i++)
	{
		if (number[i] < '0' || number[i] > '9')
			return (false);
	}
	return (true);
}

Contact	Contact::DefineNew( void )
{
	Contact contact;

	std::cout << "First Name: ";
	std::cin >> contact.first_name;
	std::cout << "Last Name: ";
	std::cin >> contact.last_name;
	std::cout << "Nickname: ";
	std::cin >> contact.nick_name;
	while (1)
	{
		std::cout << "Phone Number: ";
		std::cin >> contact.phone_number;
		if (check_number(contact.phone_number))
			break ;
		else
			std::cout << "Invalid Number, only digits are accepted" << std::endl;
	}
	std::cout << "Darkest Secret: ";
	std::cin.ignore();
	std::getline(std::cin, contact.darkest_secret);
	std::cout << "Contact created" << std::endl;

	return contact;
}

void	Contact::FirstNameSet(std::string first_name)
{
	this->first_name = first_name;
}

void	Contact::LastNameSet(std::string last_name)
{
	this->last_name = last_name;
}

void	Contact::NickNameSet(std::string nick_name)
{
	this->nick_name = nick_name;
}

std::string	Contact::FirstNameGet( void ) const
{
	return this->first_name;
}

std::string	Contact::LastNameGet( void ) const
{
	return this->last_name;
}

std::string	Contact::NickNameGet( void ) const
{
	return this->nick_name;
}

std::string	Contact::PrintFormat(std::string str)
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
	std::cin.ignore();
}
