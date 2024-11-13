/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:27:48 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/29 20:34:13 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP

# include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
	public:
		FragTrap( void );
		FragTrap(const char *);
		FragTrap(const FragTrap &);
		FragTrap &operator=(const FragTrap &);
		~FragTrap( void );

		void	highFivesGuys( void );
	private:
		
};

#endif // !FRAG_TRAP_HPP
