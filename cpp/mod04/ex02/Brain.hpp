/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:30:57 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 23:31:58 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_CPP
# define BRAIN_CPP

#include <string>

class Brain
{
public:
	Brain();
	~Brain();

	Brain(const Brain &);
	Brain &operator=(const Brain &);

private:
	std::string ideas[100];
};

#endif // BRAIN_CPP
