/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:21 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 16:52:24 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"

#define TEST_BUROCRAT_COUNT 3

void    test_burocrat(AForm* form) {
    if (form == NULL) {
        std::cout << "Form parameter is NULL" << std::endl;
        return ;
    }

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
    Intern a;

    AForm *test = NULL;
    test = a.makeForm("shurbbery", "shrub_target");
    test_burocrat(test);
    delete test;
    test = a.makeForm("robotomy request", "rob_target");
    test_burocrat(test);
    delete test;
    test = a.makeForm("presidential pardon", "pres_target");
    test_burocrat(test);
    delete test;
    test = a.makeForm("unknown form", "none");
    test_burocrat(test);
    delete test;
    return 0;
}
