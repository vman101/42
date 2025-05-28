/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:53:57 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/28 12:32:50 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"
#include <iostream>

void    test_equip(ICharacter *me) {
    std::cout << std::endl << "===== Testing Equip =====" << std::endl << std::endl;

    AMateria* tmp;
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    me->equip(tmp);
    me->equip(tmp);
    ICharacter* bob = new Character("bob");
    *me = *bob;
    delete bob;
    delete src;
}

void test_materia() {
    std::cout << std::endl << "===== Testing Materia =====" << std::endl << std::endl;
    {
        AMateria *ice = new Ice();
        delete ice;
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        ice = new Cure();
        delete ice;
        ice = new Cure();
    }
}

void test_materia_source() {
    std::cout << std::endl << "===== Testing MateriaSource =====" << std::endl << std::endl;
    {
        IMateriaSource* src = new MateriaSource();
        src->createMateria("ice");
        src->createMateria("");
        src->learnMateria(new Ice());
        src->createMateria("cure");
        src->createMateria("");
        delete src;
    }
    {
        IMateriaSource* src = new MateriaSource();
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());
        src->learnMateria(new Cure());
        src->learnMateria(new Cure());
        src->learnMateria(new Cure());
        src->learnMateria(new Cure());
        delete src;
    }
    {
        IMateriaSource* src = new MateriaSource();
        IMateriaSource* src2(src);
        AMateria* tmp = NULL;
        src2->learnMateria(tmp);
        tmp = new Ice();
        src->learnMateria(tmp);
        src->learnMateria(tmp);
        src2->learnMateria(tmp);
        MateriaSource free = *(static_cast<MateriaSource *>(src));

        delete src;

        tmp = free.createMateria("ice");
    }
}

void test_unequip(ICharacter *me) {
    std::cout << std::endl << "===== Testing Unequip =====" << std::endl << std::endl;
    me->unequip(-1);
    me->unequip(50);
    me->unequip(3);
    me->unequip(2);
    me->unequip(1);
    me->unequip(0);
    me->unequip(0);
    AMateria *ice = new Ice();
    me->equip(ice);
    ICharacter *bob = new Character("bib");
    me->use(0, *bob);
    me->unequip(0);
    me->use(0, *bob);
    delete bob;
}

void test_subject() {
    std::cout << std::endl << "===== Testing Subject =====" << std::endl << std::endl;

    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    ICharacter* me = new Character("me");
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    ICharacter* bob = new Character("bob");
    me->use(0, *bob);
    me->use(1, *bob);
    delete bob;
    delete me;
    delete src;
}

int main()
{
    ICharacter* me = new Character("me");
    test_equip(me);
    test_unequip(me);
    test_equip(me);

    test_materia();
    test_materia_source();

    delete me;

    test_subject();

    return 0;
}
