/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:50:18 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 16:17:32 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include <iostream>

AForm::AForm() :
    _name("Undefined"),
    _is_signed(false),
    _sign_grade(150),
    _exec_grade(150)
{
    std::cout << "AForm constructor called" << std::endl;
}

AForm::AForm(const char *name, int signgrade, int execgrade) :
    _name(name),
    _is_signed(false),
    _sign_grade(signgrade),
    _exec_grade(execgrade)
{
    std::cout << "AForm Param constructor called" << std::endl;
    if (signgrade < GRADE_MAX) {
        throw AForm::GradeTooHighException();
    } else if (signgrade > GRADE_MIN) {
        throw AForm::GradeTooHighException();
    } else if (execgrade < GRADE_MAX) {
        throw AForm::GradeTooHighException();
    } else if (execgrade > GRADE_MIN) {
        throw AForm::GradeTooHighException();
    }
}

AForm::~AForm()
{
    std::cout << "AForm destructor called" << std::endl;
}

AForm::AForm(const AForm& other) :
    _name(other.getName()),
    _is_signed(other.isSigned()),
    _sign_grade(other.getSignGrade()),
    _exec_grade(other.getExecGrade())
{
    std::cout << "AForm copy constructor called" << std::endl;
}

AForm &AForm::operator=(const AForm& other)
{
    if (this != &other) {
        this->_is_signed = other._is_signed;
    }
    return (*this);
}

const std::string   &AForm::getName() const
{
    return this->_name;
}

int   AForm::getSignGrade() const
{
    return  this->_sign_grade;
}

int   AForm::getExecGrade() const
{
    return  this->_exec_grade;
}

bool        AForm::isSigned() const
{
    return  this->_is_signed;
}


const char *AForm::GradeTooLowException::what() const throw()
{
    return "[AForm] Grade is too low!";
}

const char *AForm::GradeTooHighException::what() const throw()
{
    return "[AForm] Grade is too high!";
}

const char *AForm::FormNotSignedException::what() const throw()
{
    return "[AForm] Form hasnt been signed!";
}

void        AForm::unsign_debug() {
    this->_is_signed = false;
}

void        AForm::beSigned(const Bureaucrat &signer)
{
    if (signer.getGrade() > this->getSignGrade()) {
        throw AForm::GradeTooLowException();
    } else if (signer.getGrade() < 1) {
        throw AForm::GradeTooHighException();
    } else if (this->_is_signed == true) {
        std::cout << "AForm " << this->_name << " has already been signed!" << std::endl;
    } else {
        this->_is_signed = true;
    }
}
