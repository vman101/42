/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:37:33 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/23 16:06:02 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

void ltrim_inplace(std::string& str) {
    std::string::size_type pos = str.find_first_not_of(" \t\n\r");
    if (pos != std::string::npos) {
        str.erase(0, pos);
    } else {
        str.clear();
    }
}

void rtrim_inplace(std::string& str) {
    std::string::size_type pos = str.find_last_not_of(" \t\n\r");
    if (pos != std::string::npos) {
        str.erase(pos + 1);
    } else {
        str.clear();
    }
}

void trim_inplace(std::string& str) {
    rtrim_inplace(str);
    ltrim_inplace(str);
}
