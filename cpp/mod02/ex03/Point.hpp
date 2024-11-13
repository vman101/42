/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:23:23 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/29 17:16:28 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point
{
	public:
		Point();
		Point(const float x, const float y);
		Point(const Point &);
		~Point();

		Point &operator=(const Point &);

		const Fixed	&getX( void ) const;
		const Fixed	&getY( void ) const;

	private:
		const Fixed _x;
		const Fixed _y;
};

bool	bsp(Point const &a, Point const &b, Point const &c, Point const &point);
Fixed	triangle_area_calculate(Point const &a, Point const &b, Point const &c);

#endif // !POINT_HPP
