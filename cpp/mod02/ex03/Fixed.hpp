/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:46:58 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/12 16:16:06 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

# define EPSILON 1
# define FRACTION_COUNT 8

class Fixed
{
	public:
		Fixed();
		Fixed(const int value);
		Fixed(const float value);
		Fixed(const Fixed &);
		~Fixed();

		Fixed	&operator=( const Fixed & );

		bool	operator<( const Fixed & ) const;
		bool	operator>( const Fixed & ) const;
		bool	operator<=( const Fixed & ) const;
		bool	operator>=( const Fixed & ) const;
		bool	operator==( const Fixed & ) const;
		bool	operator!=( const Fixed & ) const;

		Fixed	operator+( const Fixed & ) const; 
		Fixed	operator-( const Fixed & ) const; 
		Fixed	operator*( const Fixed & ) const; 
		Fixed	operator/( const Fixed & ) const;

		Fixed	&operator++( void );
		Fixed	&operator--( void );
		Fixed	operator++( int );
		Fixed	operator--( int );

		static Fixed	&min(Fixed &a, Fixed &b);
		static Fixed	&max(Fixed &a, Fixed &b);

		static const Fixed	&min(const Fixed &a, const Fixed &b);
		static const Fixed	&max(const Fixed &a, const Fixed &b);
		static Fixed	abs(const Fixed &);


		int		getRawBits( void ) const;
		void	setRawBits( int const raw );
		float	toFloat( void ) const;
		int		toInt( void ) const;

	private:
		static const int	fraction_count = FRACTION_COUNT;
		int					_value;
};

std::ostream &operator<<(std::ostream &out, const Fixed &other);
#endif
