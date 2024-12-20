/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:39:48 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 21:37:23 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
	public:
		ScavTrap();
		ScavTrap(const char *);
		ScavTrap(const ScavTrap &);
		ScavTrap&operator=(const ScavTrap &);
		~ScavTrap();

		void	guardGate( void );
		void	attack( const std::string &target );
	private:

};

#endif
