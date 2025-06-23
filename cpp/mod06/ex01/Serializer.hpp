/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:46:00 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/23 18:06:36 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include "Data.hpp"
# include <inttypes.h>

class Serialzer
{
public:
    static uintptr_t   serialize(Data *);
    static Data        *deserialize(uintptr_t);
private:
    Serialzer();
    ~Serialzer();

    Serialzer(const Serialzer &);
    Serialzer &operator=(const Serialzer &);

};

#endif // SERIALIZER_HPP
