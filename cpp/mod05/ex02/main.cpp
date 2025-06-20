/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:21 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 16:11:04 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonFrom.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyForm.hpp"

#define TEST_BUROCRAT_COUNT 3

void    test_burocrat(AForm* form) {
    Bureaucrat b[TEST_BUROCRAT_COUNT] = {
        Bureaucrat("no_sign_no_exec", 150),
        Bureaucrat("sign_no_exec", form->getExecGrade() + 1),
        Bureaucrat("sign_and_exec", form->getExecGrade())
    };

    for (int i = 0; i < TEST_BUROCRAT_COUNT; i++) {
        try {
            b[i].signForm(*form);
            b[i].executeForm(*form);
        }
        catch( std::exception &e )
        {
            std::cout << "[EXCEPTION] caught: " << e.what() << std::endl;
        }
        form->unsign_debug();
    }
}

int main ( void )
{
    {
        AForm *shurb = new ShrubberyForm("shrub_target");
        test_burocrat(shurb);
        delete shurb;
    }
    {
        AForm *rob = new RobotomyRequestForm("rob_target");
        test_burocrat(rob);
        delete rob;
    }
    {
        AForm *pres = new PresidentialPardonForm("pres_target");
        test_burocrat(pres);
        delete pres;
    }

    return 0;
}
