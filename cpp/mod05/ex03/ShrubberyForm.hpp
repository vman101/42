/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyForm.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:49:18 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 16:42:46 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHURBBERY_FROM_HPP
# define SHURBBERY_FROM_HPP

# include "AForm.hpp"
#include "Bureaucrat.hpp"

# define DJB2_SHRUB_HASH 249891601603629480UL
# define SHRUB_SIGN_GRADE 145
# define SHRUB_EXEC_GRADE 137

class ShrubberyForm : public AForm
{
public:
    ShrubberyForm(const char *target);
    ~ShrubberyForm();

    ShrubberyForm(const ShrubberyForm &);
    ShrubberyForm &operator=(const ShrubberyForm &);

    virtual void execute(const Bureaucrat&) const;

private:
    const std::string _target;
};

#endif // !SHURBBERY_FROM_HPP
