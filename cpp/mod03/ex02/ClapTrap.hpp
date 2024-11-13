/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:46:01 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/29 20:18:21 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAP_TRAP_HPP
# define CLAP_TRAP_HPP

#include <string>

class ClapTrap
{
	public:
		ClapTrap();
		ClapTrap(const char *);
		ClapTrap(const ClapTrap &);
		ClapTrap &operator=(const ClapTrap &);
		~ClapTrap();

		void	attack(const std::string &target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

	protected:
		std::string _name;
		int			_hit_points;
		int			_energy_points;
		int			_attack_damage;
};

#endif // !CLAP_TRAP_HPP
