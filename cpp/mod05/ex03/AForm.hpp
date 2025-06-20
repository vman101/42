/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:40:48 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 16:06:19 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

#include "Bureaucrat.hpp"
#include <string>

#define GRADE_MAX 1
#define GRADE_MIN 150

class AForm
{
public:
    AForm();
    virtual ~AForm();

    AForm(const AForm &);
    AForm(const char *, int, int);
    AForm &operator=(const AForm &);

    class GradeTooLowException : public std::exception
    {
        const char *what() const throw();
    };

    class GradeTooHighException : public std::exception
    {
        const char *what() const throw();
    };

    class FormNotSignedException : public std::exception
    {
        const char *what() const throw();
    };

    const std::string   &getName() const;
    int                 getSignGrade() const;
    int                 getExecGrade() const;
    bool                isSigned() const;

    void                beSigned(const Bureaucrat&);
    virtual void        execute(const Bureaucrat& ) const = 0;

    void                unsign_debug();

private:
    const std::string   _name;
    bool                _is_signed;
    const int           _sign_grade;
    const int           _exec_grade;
};

#endif // FORM_HPP
