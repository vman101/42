#include "MateriaSource.hpp"
#include "AMateria.hpp"
#include "IMateriaSource.hpp"
#include "DynamicArray.hpp"

#include <iostream>

MateriaSource::MateriaSource() :
    IMateriaSource(),
    _materia_count(0)
{
    for (unsigned int i = 0; i < MATERIA_BUFFER_SIZE; i++) {
        this->_materia_buffer[i] = NULL;
    }

    std::cout << "MateriaSource constructor called" << std::endl;
}

MateriaSource::~MateriaSource()
{
    std::cout << "MateriaSource destructor called" << std::endl;
}

MateriaSource::MateriaSource(const MateriaSource& other) :
    IMateriaSource(),
    _materia_count(other._materia_count)
{
    for (unsigned int i = 0; i < MATERIA_BUFFER_SIZE; i++) {
        /*this->_materia_buffer[i].delete_me();*/
        this->_materia_buffer[i] = NULL;
    }

    for (unsigned int i = 0; i < MATERIA_BUFFER_SIZE; i++) {
        if (other._materia_buffer[i]) {
            this->_materia_buffer[i] = other._materia_buffer[i]->clone();
        } else {
            this->_materia_buffer[i] = NULL;
        }
    }
    std::cout << "MateriaSource copy constructor called" << std::endl;
}

MateriaSource &MateriaSource::operator=(const MateriaSource& other)
{
    if (this != &other) {
        this->_materia_count = other._materia_count;
        for (unsigned int i = 0; i < MATERIA_BUFFER_SIZE; i++) {
            if (other._materia_buffer[i]) {
                this->_materia_buffer[i] = other._materia_buffer[i]->clone();
            } else {
                this->_materia_buffer[i] = NULL;
            }
        }
    }
    return (*this);
}

AMateria *MateriaSource::createMateria(std::string const & type) {
    for (unsigned int i = 0; i < MATERIA_BUFFER_SIZE; i++) {
        if (this->_materia_buffer[i] && this->_materia_buffer[i]->getType() == type) {
            std::cout << "[MATERIA_CREATE] Created Materia " << this->_materia_buffer[i]->getType() << std::endl;
            return this->_materia_buffer[i]->clone();
        }
    }
    return NULL;
}

void MateriaSource::learnMateria(AMateria* new_materia) {
    if (this->_materia_count == MATERIA_BUFFER_SIZE) {
        std::cout << "[MATERIA_LEARN_ERROR] This MaterialSource has no more Slots left" << std::endl;
    } else if (!new_materia){
        std::cout << "[MATERIA_LEARN_ERROR] This Material is NULL" << std::endl;
    } else {
        this->_materia_buffer[this->_materia_count] = new_materia->clone();
        std::cout << "[MATERIA_LEARN] Learned Materia "
            << this->_materia_buffer[_materia_count]->getType()
            << std::endl;
        this->_materia_count++;
    }
}
