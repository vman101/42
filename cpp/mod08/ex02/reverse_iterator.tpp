/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:38:16 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 19:43:59 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <cstddef>
# include <exception>

template <typename T>
class MutantStack<T>::reverse_iterator {
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

    reverse_iterator(T *position, size_t count): position(position), bottom(position), count(count) {}
    reverse_iterator(T *position, size_t count, int): position(position + count), bottom(position), count(count) {}
    ~reverse_iterator() {}

    reverse_iterator(iterator &other): position(other.position), bottom(other.bottom), count(other.count) {}
    reverse_iterator(const iterator &other): position(other.position), bottom(other.bottom), count(other.count) {}

    reverse_iterator &operator=(const iterator &other) {
        if (this != &other) {
            this->bottom = other.bottom;
            this->position = other.position;
            this->count = other.count;
        }
        return (*this);
    }

    bool operator!=(const reverse_iterator &other) {
        return this->position != other.position;
    }

    bool operator==(const reverse_iterator &other) {
        return this->position == other.position;
    }

    T& operator*( void ) {
        if (position > bottom + count) {
            throw IteratorOutOfBounds();
        }
        return *this->position;
    }

    reverse_iterator operator--(int) {
        if (position == bottom + count - 1) {
            throw IteratorOutOfBounds();
        }
        reverse_iterator save_pos(*this);
        position++;
        return save_pos;
    }

    reverse_iterator &operator--(void) {
        if (position == bottom + count - 1) {
            throw IteratorOutOfBounds();
        }
        position++;
        return *this;
    }

    reverse_iterator operator++(int) {
        if (position == bottom) {
            throw IteratorOutOfBounds();
        }
        reverse_iterator save_pos(*this);
        position--;
        return save_pos;
    }

    reverse_iterator &operator++(void) {
        if (position == bottom) {
            throw IteratorOutOfBounds();
        }
        position--;
        return *this;
    }
};

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rbegin( void ) {
    return reverse_iterator(this->getData(), this->size(), 0);
}

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rend( void ) {
    return reverse_iterator(this->getData(), this->size());
}
