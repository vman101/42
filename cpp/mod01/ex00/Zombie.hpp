/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:56:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/22 13:25:33 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>

class Zombie
{
	public:
		Zombie( void );
		Zombie(std::string name);
		~Zombie( void );

		void	announce( void );
	private:
		std::string name;
};

void	randomChump(std::string name);
Zombie	*newZombie(std::string name);

#endif
