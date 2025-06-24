/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_iterator.tpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:11:48 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 19:34:22 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cstddef>
# include <exception>

template <typename T>
class MutantStack<T>::const_iterator {
private:
    T       *position;
    T       *bottom;
    size_t  count;
public:

    class IteratorOutOfBounds: public std::exception {
        const char * what() const throw() {
            return "Trying to access member out of bounds";
        }
    };

    const_iterator(T *position, size_t count): position(position), bottom(position), count(count) {}
    const_iterator(T *position, size_t count, int): position(position + count), bottom(position), count(count) {}
    ~const_iterator() {}

    const_iterator(iterator &other): position(other.position), bottom(other.bottom), count(other.count) {}
    const_iterator(const iterator &other): position(other.position), bottom(other.bottom), count(other.count) {}

    const_iterator &operator=(const iterator &other) {
        if (this != &other) {
            this->bottom = other.bottom;
            this->position = other.position;
            this->count = other.count;
        }
        return (*this);
    }

    bool operator!=(const const_iterator &other) {
        return this->position != other.position;
    }

    bool operator==(const const_iterator &other) {
        return this->position == other.position;
    }

    T& operator*( void ) {
        if (position >= bottom + count) {
            throw IteratorOutOfBounds();
        }
        return *this->position;
    }

    const_iterator operator--(int) {
        if (position == bottom) {
            throw IteratorOutOfBounds();
        }
        const_iterator save_pos(*this);
        position--;
        return save_pos;
    }

    const_iterator &operator--(void) {
        if (position == bottom) {
            throw IteratorOutOfBounds();
        }
        position--;
        return *this;
    }

    const_iterator operator++(int) {
        if (position == bottom + count) {
            throw IteratorOutOfBounds();
        }
        const_iterator save_pos(*this);
        position++;
        return save_pos;
    }

    const_iterator &operator++(void) {
        if (position == bottom + count) {
            throw IteratorOutOfBounds();
        }
        position++;
        return *this;
    }
};

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::cbegin( void ) {
    return const_iterator(this->getData(), this->size());
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::cend( void ) {
    return const_iterator(this->getData(), this->size(), 0);
}
