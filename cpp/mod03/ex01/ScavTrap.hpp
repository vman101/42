/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:39:48 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 14:58:49 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

# define SCAVTRAP_DEF_HP 100
# define SCAVTRAP_DEF_EP 50
# define SCAVTRAP_DEF_ATK 20

# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
public:
    ScavTrap();
    ScavTrap(const char *);
    ScavTrap(const ScavTrap &);
    ScavTrap&operator=(const ScavTrap &);
    ~ScavTrap();

    void    guardGate( void );
    void    attack( const std::string &target );
private:

};

#endif
