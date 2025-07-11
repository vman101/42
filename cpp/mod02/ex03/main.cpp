/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:45:30 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/12 16:14:51 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Point.hpp"

void	test_in_triangle()
{
	Point inside(2., 2.);
	bool hit = bsp(Point(0., 0.), Point(10, 0.), Point(0., 10.), inside);

	std::cout << "triangle hit = " << hit << std::endl;
}

void	test_out_triangle()
{
	Point outside(100., 100.);
	bool hit = bsp(Point(0., 0.), Point(10, 0.), Point(0., 10.), outside);

	std::cout << "triangle hit = " << hit << std::endl;
}

int main( void )
{
	test_in_triangle();
	test_out_triangle();
	return 0;
}
