/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicArray.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:34:37 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 16:14:53 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMICARRAY_HPP
# define DYNAMICARRAY_HPP

#include "AMateria.hpp"
#define VECTOR_DEFAULT_CAP 32

class DynamicArray
{
public:
    DynamicArray();
    ~DynamicArray();
    DynamicArray(const DynamicArray &);
    DynamicArray &operator=(const DynamicArray &);

    void push(AMateria *);
    void push_unique(AMateria *);

private:
    AMateria        **_members;
    int    _count;
    int    _cap;
};

#endif // DYNAMICARRAY_HPP
