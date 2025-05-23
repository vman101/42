/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:52:28 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 15:22:54 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMOND_TRAP_HPP
#define DIAMOND_TRAP_HPP

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap
{
public:
    DiamondTrap();
    DiamondTrap(std::string);
    DiamondTrap(const DiamondTrap &);
    DiamondTrap &operator=(const DiamondTrap &);
    ~DiamondTrap();

    void whoAmI(void);
    void attack(const std::string& target);

private:
    std::string _name;
};

#endif // !DIAMOND_TRAP_HPP
