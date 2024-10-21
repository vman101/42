/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:02:34 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/21 16:54:26 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"phonebook.hpp"
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
	Contact contact;

	contact = contact.DefineNew();
	this->contact[this->contact_cursor % MAX_CONTACT] = contact;
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
		std::cout << std::setw(10) << std::right << this->contact[i].FirstNameGet() << "|";
		std::cout << std::setw(10) << std::right << this->contact[i].LastNameGet() << "|";
		std::cout << std::setw(10) << std::right << this->contact[i].NickNameGet() << std::endl;
	}
}

void	Phonebook::Search( void )
{
	int	index;

	if (this->contact_count > 0)
		this->Display();
	std::cout << "Enter index: " << std::endl;
	std::cin >> index;
	if (index >= 0 && index < 8)
		this->contact[index].Display();
}
