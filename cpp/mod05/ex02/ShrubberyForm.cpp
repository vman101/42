/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyForm.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:53:36 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 16:39:43 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>
#include <iostream>

ShrubberyForm::ShrubberyForm(const char *target) :
    AForm("Shrub", SHRUB_SIGN_GRADE, SHRUB_EXEC_GRADE),
    _target(target)
{
    std::cout << "ShrubberyForm constructor called" << std::endl;
}

ShrubberyForm::~ShrubberyForm()
{
    std::cout << "ShrubberyForm destructor called" << std::endl;
}

ShrubberyForm::ShrubberyForm(const ShrubberyForm& other) :
    AForm(other.getName().c_str(), other.getSignGrade(), other.getExecGrade())
{
    std::cout << "ShrubberyForm copy constructor called" << std::endl;
}

ShrubberyForm &ShrubberyForm::operator=(const ShrubberyForm& other)
{
    (void)other;
    return (*this);
}

void ShrubberyForm::execute(const Bureaucrat& executor) const {
    if (this->isSigned() == false) {
        throw AForm::FormNotSignedException();
    } else if (executor.getGrade() > this->getExecGrade()) {
        throw AForm::GradeTooLowException();
    }
    std::ofstream output(std::string(this->_target + "_shrubbery").c_str());
    if (output.is_open() == false) {
        std::cerr << "[ERROR] Failed to open file " << std::endl;
    }

    const char *tree =
        "       _-_\n"
        "    /~~   ~~\\\n"
        " /~~         ~~\\\n"
        "{               }\n"
        " \\  _-     -_  /\n"
        "   ~  \\\\ //  ~\n"
        "_- -   | | _- _\n"
        "  _ -  | |   -_\n"
        "      // \\\\\n";

    for (int i = 0; i < 3; i++)
        output << tree;
}
