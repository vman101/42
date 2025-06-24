/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:57:35 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 15:20:26 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <exception>
# include <algorithm>

class MemberNotFound: public std::exception {
    const char * what() const throw() {
        return "member not found";
    }
};

template <typename T>
int   easyfind(T container, int value) {
    typename T::iterator ret = std::find(container.begin(), container.end(), value);
    if (ret == container.end()) {
        throw MemberNotFound();
    }
    return *ret;
}

#endif // SPAN_HPP
