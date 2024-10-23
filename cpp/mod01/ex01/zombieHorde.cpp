/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:44:34 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/22 18:10:09 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name)
{
	Zombie *horde = new Zombie[N];

	if (N < 0)
		return NULL;
	for (int i = 0; i < N; i++)
	{
		horde[i].name_set(name);
	}
	return horde;
}
