/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:28:49 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 12:53:09 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

# include <iostream>

template <typename T>
void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
void swap(const T &a, const T &b) {
    (void)a;
    (void)b;
    std::cout << "Cant swap const type values" << std::endl;
}

template <typename T>
T min(T &a, T &b) {
    if (a < b) {
        return a;
    }
    return b;
}

template <typename T>
T max(T &a, T &b) {
    if (a > b) {
        return a;
    }
    return b;
}

#endif // WHATEVER_HPP
