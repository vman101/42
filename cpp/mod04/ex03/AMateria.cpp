#include "AMateria.hpp"
#include "ICharacter.hpp"

#include <iostream>
#include <new>

DynamicArray AMateria::_memory_collector = DynamicArray();

AMateria::AMateria() :
    _type("default")
{
    std::cout << "AMateria constructor called" << std::endl;
}

AMateria::AMateria(const std::string& type) :
    _type(type)
{
    std::cout << "AMateria constructor called" << std::endl;
}

AMateria::~AMateria()
{
    std::cout << "AMateria destructor called" << std::endl;
}

AMateria::AMateria(const AMateria& other)
{
    this->_type = other._type;
    std::cout << "AMateria copy constructor called" << std::endl;
}

AMateria &AMateria::operator=(const AMateria& other)
{
    if (this != &other) {
        this->_type = other._type;
    }
    return (*this);
}

void *AMateria::operator new(size_t size) {
    void *tmp = ::operator new(size);
    _memory_collector.push_unique(tmp);
    return tmp;
}

void AMateria::operator delete(void *member) {
    _memory_collector.remove(member);
    /*AMateria *tmp = static_cast<AMateria *>(member);*/
    /*tmp->~AMateria();*/
    ::operator delete(member);
}

std::string const& AMateria::getType() const {
    return this->_type;
}

void AMateria::use(ICharacter& target) {
    std::cout << "* does something to " << target.getName() << std::endl;
}
