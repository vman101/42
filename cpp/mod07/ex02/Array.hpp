/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:22:01 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 15:34:56 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <exception>

template <typename T>
class Array
{
public:
    Array(): _count(0), _members(NULL) { }

    ~Array() {
        delete[] this->_members;
    }

    Array(const Array& other): _count(other._count) {
        this->_members = new T[this->_count];
        for (unsigned int i = 0; i < other._count; i++) {
            this->_members[i] = other._members[i];
        }
    }

    Array(unsigned int n): _count(n), _members(new T[n]) {
    }

    Array &operator=(const Array& other)
    {
        if (this != &other)
        {
            if (this->_count < other._count) {
                delete[] this->_members;
                this->_members = new T[other._count];
            }
            for (unsigned int i = 0; i < other._count; i++) {
                this->_members[i] = other._members[i];
            }
            this->_count = other._count;
        }
        return (*this);
    }

    T &operator[](unsigned int index) {
        if (index < this->_count || this->_count == 0) {
            return _members[index];
        }
        throw OutOfBoundsException();
    }

    class OutOfBoundsException: public std::exception {
        const char * what() const throw() {
            return "Trying to access array out of bounds";
        }
    };

    unsigned int size() const {
        return this->_count;
    }

private:
    unsigned int    _count;
    T               *_members;
};

#endif // ARRAY_HPP
