/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicArray.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:34:37 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/28 11:51:30 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMICARRAY_HPP
# define DYNAMICARRAY_HPP

#define VECTOR_DEFAULT_CAP 32

class AMateria;

class DynamicArray
{
public:
    DynamicArray();
    ~DynamicArray();
    DynamicArray(const DynamicArray &);
    DynamicArray &operator=(const DynamicArray &);

    void push(void *);
    void push_unique(void *);
    void remove(void *);

private:
    void        **_members;
    int    _count;
    int    _cap;

    void manual_delete(void *member);
};

#endif // DYNAMICARRAY_HPP
