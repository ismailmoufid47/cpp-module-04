#include "Character.hpp"

#include <iostream>

Character::Character() : name("default"), floorCount(0), count(0) {}

Character::Character(const std::string &name) : name(name), floorCount(0), count(0) {}

Character::Character(const Character &other) : name(other.name), floorCount(0), count(0)
{
	*this = other;
}

Character &Character::operator=(const Character &other)
{
	if (this != &other)
	{
		name = other.name;

		for (int i = 0; i < count; i++)
			delete inventory[i];

		count = other.count;

		for (int i = 0; i < count; i++)
			inventory[i] = other.inventory[i]->clone();

		for (int i = 0; i < floorCount; i++)
			delete floor[i];
		floorCount = 0;
	}
	return *this;
}

Character::~Character()
{
	for (int i = 0; i < count; i++)
		delete inventory[i];

	for (int i = 0; i < floorCount; i++)
		delete floor[i];
}

std::string const &Character::getName() const
{
	return name;
}

void Character::equip(AMateria *m)
{
	if (count < 4 && m)
	{
		inventory[count] = m;
		count++;
	}
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= count || !inventory[idx])
		return;

	if (floorCount < 1000)
		floor[floorCount++] = inventory[idx];
	else
		delete inventory[idx];

	for (int i = idx; i < count - 1; i++)
		inventory[i] = inventory[i + 1];
	inventory[count - 1] = nullptr;
	count--;
}

void Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx >= count || !inventory[idx])
		return;

	inventory[idx]->use(target);
}
