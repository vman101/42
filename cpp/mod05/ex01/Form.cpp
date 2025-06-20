/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:50:18 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/17 11:34:45 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include <iostream>

Form::Form() :
    _name("Undefined"),
    _is_signed(false),
    _sign_grade(150),
    _exec_grade(150)
{
    std::cout << "Form constructor called" << std::endl;
}

Form::Form(const char *name, int signgrade, int execgrade) :
    _name(name),
    _is_signed(false),
    _sign_grade(signgrade),
    _exec_grade(execgrade)
{
    std::cout << "Form Param constructor called" << std::endl;
    if (signgrade < GRADE_MAX) {
        throw Form::GradeTooHighException();
    } else if (signgrade > GRADE_MIN) {
        throw Form::GradeTooHighException();
    } else if (execgrade < GRADE_MAX) {
        throw Form::GradeTooHighException();
    } else if (execgrade > GRADE_MIN) {
        throw Form::GradeTooHighException();
    }
}

Form::~Form()
{
    std::cout << "Form destructor called" << std::endl;
}

Form::Form(const Form& other) :
    _name(other.getName()),
    _is_signed(other.isSigned()),
    _sign_grade(other.getSignGrade()),
    _exec_grade(other.getExecGrade())
{
    std::cout << "Form copy constructor called" << std::endl;
}

Form &Form::operator=(const Form& other)
{
    if (this != &other) {
        this->_is_signed = other._is_signed;
    }
    return (*this);
}

const std::string   &Form::getName() const
{
    return this->_name;
}

int   Form::getSignGrade() const
{
    return  this->_sign_grade;
}

int   Form::getExecGrade() const
{
    return  this->_exec_grade;
}

bool        Form::isSigned() const
{
    return  this->_is_signed;
}


const char *Form::GradeTooLowException::what() const throw()
{
    return "[Form] Grade is too low!";
}

const char *Form::GradeTooHighException::what() const throw()
{
    return "[Form] Grade is too high!";
}

void        Form::beSigned(const Bureaucrat &signer)
{
    if (signer.getGrade() > this->getSignGrade()) {
        throw Form::GradeTooLowException();
    } else if (signer.getGrade() < 1) {
        throw Form::GradeTooHighException();
    } else if (this->_is_signed == true) {
        std::cout << "Form " << this->_name << " has already been signed!" << std::endl;
    } else {
        std::cout << "Form " << this->_name << " signed!" << std::endl;
        this->_is_signed = true;
    }
}
