/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:05:00 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 19:34:44 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cstddef>
# include <exception>

template <typename T>
class MutantStack<T>::iterator {
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

    iterator(T *position, size_t count): position(position), bottom(position), count(count) {}
    iterator(T *position, size_t count, int): position(position + count), bottom(position), count(count) {}
    ~iterator() {}

    iterator(iterator &other): position(other.position), bottom(other.bottom), count(other.count) {}
    iterator(const iterator &other): position(other.position), bottom(other.bottom), count(other.count) {}

    iterator &operator=(const iterator &other) {
        if (this != &other) {
            this->bottom = other.bottom;
            this->position = other.position;
            this->count = other.count;
        }
        return (*this);
    }

    bool operator!=(const iterator &other) {
        return this->position != other.position;
    }

    bool operator==(const iterator &other) {
        return this->position == other.position;
    }

    T& operator*( void ) {
        if (position > bottom + count) {
            throw IteratorOutOfBounds();
        }
        return *this->position;
    }

    iterator operator--(int) {
        if (position == bottom) {
            throw IteratorOutOfBounds();
        }
        iterator save_pos(*this);
        position--;
        return save_pos;
    }

    iterator &operator--(void) {
        if (position == bottom) {
            throw IteratorOutOfBounds();
        }
        position--;
        return *this;
    }

    iterator operator++(int) {
        if (position == bottom + count) {
            throw IteratorOutOfBounds();
        }
        iterator save_pos(*this);
        position++;
        return save_pos;
    }

    iterator &operator++(void) {
        if (position == bottom + count) {
            throw IteratorOutOfBounds();
        }
        position++;
        return *this;
    }
};

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin( void ) {
    return iterator(this->getData(), this->size());
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end( void ) {
    return iterator(this->getData(), this->size(), 0);
}
