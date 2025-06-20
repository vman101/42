/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonFrom.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:33:19 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/17 16:38:38 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIAL_PARDON_FORM_HPP
# define PRESIDENTIAL_PARDON_FORM_HPP

# include "AForm.hpp"

# define PRES_SIGN_GRADE 25
# define PRES_EXEC_GRADE 5

class PresidentialPardonForm : public AForm
{
public:
    PresidentialPardonForm(const char *);
    ~PresidentialPardonForm();

    PresidentialPardonForm(const PresidentialPardonForm &);
    PresidentialPardonForm &operator=(const PresidentialPardonForm &);

    void    execute(const Bureaucrat& ecex) const;
private:
    std::string _target;
};

#endif // PRESIDENTIAL_PARDON_FORM_HPP
