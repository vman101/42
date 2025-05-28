#include "AMateria.hpp"

class Ice : public AMateria
{
public:
    Ice();
    ~Ice();
    Ice(const Ice &);
    Ice &operator =(const Ice &);

    AMateria *clone() const;
    void use(ICharacter &target);
    bool isHeapAlloc() const;
private:
    bool    _is_heap_alloc;
};

