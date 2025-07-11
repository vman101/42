/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:15:52 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 12:00:55 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

class Base
{
public:
    virtual ~Base();

private:
};

Base    *generate(void);
void    identify(Base *p);
void    identify(Base &p);

#endif // BASE_HPP
