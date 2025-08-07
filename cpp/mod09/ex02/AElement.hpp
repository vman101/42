/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AElement.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:39:27 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/07 17:21:53 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AELEMENT_HPP
# define AELEMENT_HPP

class AElement
{
public:
    AElement();
    virtual ~AElement();

    AElement(const AElement &);
    AElement &operator=(const AElement &);

    virtual AElement    *getA( void ) = 0;
    virtual AElement    *getB( void ) = 0;
    virtual void        print( void ) = 0;
    virtual void        print_value( void ) = 0;
    virtual int         getValue( void ) = 0;

private:
};

#endif // AELEMENT_HPP
