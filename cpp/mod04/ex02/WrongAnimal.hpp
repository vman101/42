/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:06:18 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 16:02:12 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <string>

class WrongAnimal {
public:
	WrongAnimal();
	~WrongAnimal();

	WrongAnimal(const std::string &);
	WrongAnimal(const WrongAnimal &);
	WrongAnimal &operator=(const WrongAnimal &);

	void makeSound( void ) const;
	const std::string&	getType() const;

protected:
	std::string _type;
};

#endif // !WRONGANIMAL_HPP
