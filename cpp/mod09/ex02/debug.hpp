/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:59:15 by vvobis            #+#    #+#             */
/*   Updated: 2025/07/24 17:51:54 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template <typename T>
void    debug_container_print(T seq) {
    std::cout << seq.size() << std::endl;
    std::cout << "{" << std::endl;
    for (unsigned int i = 0; i < seq.size(); i++) {
        std::cout << "[ ";
        for (unsigned int j = 0; j < seq[i].size(); j++)
            std::cout << seq[i][j] << " ";
        std::cout << "]";
    }
    std::cout << "}" << std::endl;
}
