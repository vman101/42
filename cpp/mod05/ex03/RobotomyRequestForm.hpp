/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:13:16 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 16:42:41 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMY_REQUEST_FORM_HPP
# define ROBOTOMY_REQUEST_FORM_HPP

# include "AForm.hpp"
# include "Bureaucrat.hpp"
# include <string>

# define ROBO_SIGN_GRADE 72
# define ROBO_EXEC_GRADE 45
# define DJB2_ROBO_HASH 9164379116211002871UL

class RobotomyRequestForm : public AForm
{
public:
    RobotomyRequestForm(const char *target);
    ~RobotomyRequestForm();

    RobotomyRequestForm(const RobotomyRequestForm &);
    RobotomyRequestForm &operator=(const RobotomyRequestForm &);

    virtual void execute(const Bureaucrat &) const;

private:
    const std::string _target;
};

#endif // ROBOTOMY_REQUEST_FORM_HPP
