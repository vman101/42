/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:15:05 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 19:35:43 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include <string>
#include "Weapon.hpp"

class HumanA
{
	public:
		HumanA( std::string name, Weapon &weapon );
		~HumanA( void );

		void	setWeapon( Weapon& );
		void	attack( void ) const;
	private:
		Weapon &weapon;
		std::string name;
};

#endif
