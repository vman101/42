/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:28:23 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/23 11:25:34 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon
{
	public:
		Weapon( std::string );
		~Weapon( void );

		void setType( std::string type );
		const std::string& getType( void ) const;

	private:
		std::string type;

};

#endif
