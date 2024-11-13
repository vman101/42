/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:29:52 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/29 22:16:26 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <iostream>
#include <ostream>

Point::Point() : _x(0), _y(0)
{
	std::cout << "Default Point Constructor Called" << std::endl;
}

Point::Point(const float x, const float y) : _x(x), _y(y)
{
	std::cout << "Float Point Constructor Called" << std::endl;
}

Point::Point(const Point &)
{

}

Point::~Point()
{
}

const Fixed	&Point::getX() const
{
	return (_x);
}

const Fixed	&Point::getY() const
{
	return (_y);
}

Fixed triangle_area_calculate(Point const &a, Point const &b, Point const &c)
{
    Fixed term1 = a.getX() * (b.getY() - c.getY());
    Fixed term2 = b.getX() * (c.getY() - a.getY());
    Fixed term3 = c.getX() * (a.getY() - b.getY());

    return (Fixed::abs(term1 + term2 + term3) / 2);
}

bool	bsp(Point const &a, Point const &b, Point const &c, Point const &point)
{
	Fixed abPoint = triangle_area_calculate(a, b, point);
	Fixed bcPoint = triangle_area_calculate(b, c, point);
	Fixed caPoint = triangle_area_calculate(c, a, point);
	Fixed areaTriangle = triangle_area_calculate(a, b, c);

	if (abPoint == 0 || bcPoint == 0 || caPoint == 0)
		return (false);
	return (areaTriangle == (abPoint + bcPoint + caPoint));
}
