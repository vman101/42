/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:47:39 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 23:18:22 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : protected WrongAnimal
{
public:
	WrongCat();
	~WrongCat();

	WrongCat(const WrongCat &);
	WrongCat(const std::string &);
	WrongCat &operator=(const WrongCat &);
	void	makeSound( void ) const;
};

#endif // WRONGCAT_HPP
