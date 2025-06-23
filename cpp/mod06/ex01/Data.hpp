/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:43:35 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/23 17:44:23 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

class Data
{
public:
    Data();
    ~Data();

    Data(const Data &);
    Data &operator=(const Data &);

    int getData();

private:
    int _data;
};

#endif // DATA_HPP
