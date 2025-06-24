/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_reverse_iterator.tpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:44:45 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 19:45:51 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cstddef>
# include <exception>

template <typename T>
class MutantStack<T>::const_reverse_iterator {
private:
    const T *position;
    const T *bottom;
    size_t  count;
public:

    class IteratorOutOfBounds: public std::exception {
        const char * what() const throw() {
            return "Trying to access member out of bounds";
        }
    };

    const_reverse_iterator(T *position, size_t count): position(position), bottom(position), count(count) {}
    const_reverse_iterator(T *position, size_t count, int): position(position + count), bottom(position), count(count) {}
    ~const_reverse_iterator() {}

    const_reverse_iterator(iterator &other): position(other.position), bottom(other.bottom), count(other.count) {}
    const_reverse_iterator(const iterator &other): position(other.position), bottom(other.bottom), count(other.count) {}

    const_reverse_iterator &operator=(const iterator &other) {
        if (this != &other) {
            this->bottom = other.bottom;
            this->position = other.position;
            this->count = other.count;
        }
        return (*this);
    }

    bool operator!=(const const_reverse_iterator &other) {
        return this->position != other.position;
    }

    bool operator==(const const_reverse_iterator &other) {
        return this->position == other.position;
    }

    const T& operator*( void ) {
        if (position > bottom + count) {
            throw IteratorOutOfBounds();
        }
        return *this->position;
    }

    const_reverse_iterator operator--(int) {
        if (position == bottom + count - 1) {
            throw IteratorOutOfBounds();
        }
        const_reverse_iterator save_pos(*this);
        position++;
        return save_pos;
    }

    const_reverse_iterator &operator--(void) {
        if (position == bottom + count - 1) {
            throw IteratorOutOfBounds();
        }
        position++;
        return *this;
    }

    const_reverse_iterator operator++(int) {
        if (position == bottom) {
            throw IteratorOutOfBounds();
        }
        const_reverse_iterator save_pos(*this);
        position--;
        return save_pos;
    }

    const_reverse_iterator &operator++(void) {
        if (position == bottom) {
            throw IteratorOutOfBounds();
        }
        position--;
        return *this;
    }
};

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::crbegin( void ) {
    return const_reverse_iterator(this->getData(), this->size(), 0);
}

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::crend( void ) {
    return const_reverse_iterator(this->getData(), this->size());
}
