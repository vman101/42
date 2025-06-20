/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:24:45 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/20 16:32:22 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include "AForm.hpp"
# define DJB2_HASH 5381

class Intern
{
public:
    Intern();
    ~Intern();

    Intern(const Intern &);
    Intern &operator=(const Intern &);

    AForm *makeForm(const char *, const char *) const;
private:
};

#endif // INTERN_HPP
