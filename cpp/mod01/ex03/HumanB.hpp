/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:58:47 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/23 11:36:31 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "Weapon.hpp"

class HumanB
{
	public:
		HumanB( std::string name );
		~HumanB( void );

		void	setWeapon( Weapon& );
		void	attack( void ) const;
	private:
		Weapon *weapon;
		std::string name;
};
