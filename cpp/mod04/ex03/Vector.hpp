/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:34:37 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 15:05:11 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "AMateria.hpp"
#define VECTOR_DEFAULT_CAP 32

class Vector
{
public:
    Vector();
    ~Vector();
    Vector(const Vector &);
    Vector &operator=(const Vector &);

    void push(AMateria *);
    void push_unique(AMateria *);

private:
    AMateria        **_members;
    int    _count;
    int    _cap;
};

#endif // VECTOR_HPP
