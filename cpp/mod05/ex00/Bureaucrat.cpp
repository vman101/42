/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:56:31 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/16 12:57:33 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <iostream>

Bureaucrat::Bureaucrat(): _name("Undefined"), _grade(0)
{
	std::cout << "Bureaucrat constructor called" << std::endl;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat destructor called" << std::endl;
}

Bureaucrat::Bureaucrat(const std::string &name, int grade): _name(name), _grade(grade)
{
	if (grade > 150)
	{
		throw (Bureaucrat::GradeTooLowException());
	}
	else if (grade < 1)
	{
		throw (Bureaucrat::GradeTooHighException());
	}
	std::cout << "Bureaucrat paramter constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other): _name(other.getName()), _grade(other.getGrade())
{
	std::cout << "Bureaucrat copy constructor called" << std::endl;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this == &other)
		return (*this);
	this->setGrade(other.getGrade());
	return (*this);
}

void	Bureaucrat::incGrade( void )
{
	if (_grade - 1 < 1)
	{
		throw (Bureaucrat::GradeTooHighException());
	}
	_grade -= 1;
}

void	Bureaucrat::decGrade( void )
{
	if (_grade > 150)
	{
		throw (Bureaucrat::GradeTooLowException());
	}
	_grade += 1;
}

const std::string&	Bureaucrat::getName( void ) const
{
	return (this->_name);
}

void	Bureaucrat::setGrade(int grade)
{
	if (grade > 150)
	{
		throw (Bureaucrat::GradeTooLowException());
	}
	else if (grade < 1)
	{
		throw (Bureaucrat::GradeTooHighException());
	}
	this->_grade = grade;
}

std::ostream& operator<<(std::ostream &out, const Bureaucrat &b)
{
	out << b.getName() << ", Bureaucrat grade " << b.getGrade();
	return (out);
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade is too low!";
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";
}

int	Bureaucrat::getGrade( void ) const
{
	return (this->_grade);
}
