#pragma once

#include "ICharacter.hpp"
#include "AMateria.hpp"

class Character : public ICharacter
{
private:
	std::string name;
	AMateria *inventory[4];
	AMateria *floor[1000];
	int floorCount;
	int count;

public:
	Character();
	Character(const std::string &name);
	Character(const
		 Character &other);

	Character &operator=(const Character &other);

	virtual ~Character();

	virtual std::string const &getName() const;
	virtual void equip(AMateria *m);
	virtual void unequip(int idx);
	virtual void use(int idx, ICharacter &target);
};