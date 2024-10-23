/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:56:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/22 18:02:21 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie
{
	public:
		Zombie( void );
		Zombie(std::string name);
		~Zombie( void );

		void	name_set( std::string );
		void	announce( void ) const;
	private:
		std::string name;
};

Zombie *zombieHorde(int N, std::string name);

#endif
