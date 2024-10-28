/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:46:58 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/28 17:45:14 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed
{
	public:
		Fixed();
		Fixed(const Fixed &other);
		Fixed &operator=(const Fixed &);
		~Fixed();

		int		getRawBits( void );
		void	setRawBits( int const raw );
	private:
		static const int	fraction_count = 8;
		int					value;
		
};

#endif
