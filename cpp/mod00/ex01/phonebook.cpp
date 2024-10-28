/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:02:34 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/22 13:03:07 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"phonebook.hpp"
#include	<cstdlib>
#include	<iomanip>
#include	<iostream>

Phonebook::Phonebook( void )
{
	std::cout << "Created New Phonebook!" << std::endl;
	this->contact_cursor = 0;
	this->contact_count = 0;
}

Phonebook::~Phonebook()
{
	std::cout << "Destroying Phonebook" << std::endl;
}

void	Phonebook::Add( void )
{
	this->contact[this->contact_cursor % MAX_CONTACT] = Contact::DefineNew();
	this->contact_cursor++;
	this->contact_cursor %= MAX_CONTACT;
	if (this->contact_count < MAX_CONTACT)
		this->contact_count++;
	std::cout << "Adding Contact" << std::endl;
}

void	Phonebook::Display( void )
{
	std::cout << "Phonebook entries:" << std::endl;
	for (int i = 0; i < this->contact_count; i++) {
		std::cout << i << " |";
		std::cout << std::setw(10) << std::right << this->contact[i].PrintFormat(this->contact[i].FirstNameGet()) << "|";
		std::cout << std::setw(10) << std::right << this->contact[i].PrintFormat(this->contact[i].LastNameGet()) << "|";
		std::cout << std::setw(10) << std::right << this->contact[i].PrintFormat(this->contact[i].NickNameGet()) << std::endl;
	}
}

int	is_space(char const c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(char const *s)
{
	int			nb;
	char const	*tmp;

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

void	Phonebook::Search( void )
{
	std::string	index;

	if (this->contact_count > 0)
	{
		this->Display();
		while (index.empty() || index.length() > 1 || (index[0] < '0' && index[1] > '9'))
		{
			std::cout << "Enter index: " << std::endl;
			std::cin >> index;
			if (index.length() > 1)
				std::cout << "Invalid Index";
		}
		int index_num = ft_atoi(index.c_str());
		if (index_num >= 0 && index_num < 8)
			this->contact[index_num].Display();
	}
}
