/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:47:39 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 16:39:12 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
public:
    WrongCat();
    ~WrongCat();

    WrongCat(const WrongCat &);
    WrongCat(const std::string &);
    WrongCat &operator=(const WrongCat &);
    void    makeSound( void ) const;
};

#endif // WRONGCAT_HPP
