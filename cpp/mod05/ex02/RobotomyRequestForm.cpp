/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:18:02 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 16:20:49 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm(const char *target) :
    AForm("Robo", ROBO_SIGN_GRADE, ROBO_EXEC_GRADE),
    _target(target)
{
    std::cout << "ShrubberyForm constructor called" << std::endl;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
    std::cout << "RobotomyRequestForm destructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
{
    (void)other;
    std::cout << "RobotomyRequestForm copy constructor called" << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
    (void)other;
    return (*this);
}

void    RobotomyRequestForm::execute(const Bureaucrat &executor) const
{
    if (this->isSigned() == false) {
        throw AForm::FormNotSignedException();
    } else if (executor.getGrade() > this->getExecGrade()) {
        throw AForm::GradeTooLowException();
    }

    std::srand(std::time(0));

    if ((static_cast<uint>(std::rand()) % 100) > 49) {
        std::cout << this->_target << " was succesfully robotomized!" << std::endl;
    } else {
        std::cout << "To " << this->_target << "'s family: I have some terrible news for you..." << std::endl;
    }
}
