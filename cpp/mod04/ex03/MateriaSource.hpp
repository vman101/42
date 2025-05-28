/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:59:44 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/28 11:01:20 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

#include "AMateria.hpp"
#include "IMateriaSource.hpp"
#include "DynamicArray.hpp"

#define MATERIA_BUFFER_SIZE 4

class MateriaSource : public IMateriaSource
{
public:
    MateriaSource();
    ~MateriaSource();

    MateriaSource(const MateriaSource &);
    MateriaSource &operator=(const MateriaSource &);

    void learnMateria(AMateria*);
    AMateria* createMateria(std::string const & type);


private:
    AMateria*       _materia_buffer[MATERIA_BUFFER_SIZE];
    unsigned int    _materia_count;

    /*static DynamicArray   _memory_collector;*/
};

#endif // !MATERIASOURCE_HPP
