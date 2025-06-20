/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:50:06 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 15:58:19 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_CPP
# define BUREAUCRAT_CPP

#include <exception>
#include <string>

class AForm;

class Bureaucrat
{
public:
    Bureaucrat();
    ~Bureaucrat();

    Bureaucrat(const std::string &, int);
    Bureaucrat(const Bureaucrat &);
    Bureaucrat &operator=(const Bureaucrat &);

    class GradeTooLowException : public std::exception
    {
        const char *what() const throw();
    };

    class GradeTooHighException : public std::exception
    {
        const char *what() const throw();
    };
    const std::string&  getName( void ) const;
    void                setGrade( int );
    int                 getGrade( void ) const;
    void                incGrade( void );
    void                decGrade( void );

    void                signForm(AForm &) const ;
    void                executeForm(AForm const &) const ;

private:
    const std::string   _name;
    int                 _grade;
};

std::ostream& operator<<(std::ostream &, const Bureaucrat &);

#endif // BUREAUCRAT_CPP
