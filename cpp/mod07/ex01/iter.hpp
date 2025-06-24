/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:36:43 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 14:18:21 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

template <typename A, typename L, typename F>
void iter(A &a, L l, F f) {
    for (int i = 0; i < l; i++) {
        f(a[i]);
    }
}

template <typename A, typename L, typename F>
void iter(A const &a, L l, F const f) {
    for (int i = 0; i < l; i++) {
        f(a[i]);
    }
}

#endif // ITER_HPP
