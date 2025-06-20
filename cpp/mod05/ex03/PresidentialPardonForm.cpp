/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:35:46 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 16:54:43 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonFrom.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm(const char *target) :
    AForm("Presi", PRES_SIGN_GRADE, PRES_EXEC_GRADE),
    _target(target)
{
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other)
{
    (void)other;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm& other)
{
    (void)other;
    return (*this);
}

void    PresidentialPardonForm::execute(const Bureaucrat& executor) const {
    if (this->isSigned() == false) {
        throw AForm::FormNotSignedException();
    } else if (executor.getGrade() > this->getExecGrade()) {
        throw AForm::GradeTooLowException();
    }
    std::cout << this->_target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
    std::cout << this->_target << " executed " << this->getName() << std::endl;
}
