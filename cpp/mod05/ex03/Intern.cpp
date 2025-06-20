/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:25:53 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 16:59:45 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonFrom.hpp"
#include <iostream>

Intern::Intern()
{
}

Intern::~Intern()
{
}

Intern::Intern(const Intern& other)
{
    (void)other;
}

Intern &Intern::operator=(const Intern& other)
{
    (void)other;
    return (*this);
}

AForm *Intern::makeForm(const char *name, const char *target) const {
    unsigned long hash = DJB2_HASH;
    const char *str = name;
    AForm *ret = NULL;

    (void)target;

    while (*str++) {
        hash = ((hash << 5) + hash) + *str;
    }

    switch (hash) {
        case DJB2_SHRUB_HASH:
            ret = new ShrubberyForm(target);
            break ;
        case DJB2_ROBO_HASH:
            ret = new RobotomyRequestForm(target);
            break ;
        case DJB2_PRES_HASH:
            ret = new PresidentialPardonForm(target);
            break ;
        default:
            std::cout << "Intern couldn't create " << name << ", it doesnt exist!" << std::endl;
            return NULL;
    }
    std::cout << "Intern creates" << name << std::endl;
    return ret;
}
