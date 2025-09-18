#include "Character.hpp"

#include <iostream>

Floor *Character::floorHead = new Floor();
Floor *Character::floorTail = Character::floorHead;

Character::Character() : name("default"), count(0) {}

Character::Character(const std::string &name) : name(name), count(0) {}

Character::Character(const Character &other) : name(other.name), count(0)
{
	for (int i = 0; i < other.count; ++i)
	{
		if (other.inventory[i])
			inventory[i] = other.inventory[i]->clone();
	}
	count = other.count;
}

Character &Character::operator=(const Character &other)
{
	if (this != &other)
	{
		name = other.name;

		for (int i = 0; i < count; i++)
			unequip(i);

		count = other.count;

		for (int i = 0; i < count; i++)
			inventory[i] = other.inventory[i]->clone();
	}
	return *this;
}

Character::~Character()
{
	for (int i = 0; i < count; i++)
		delete inventory[i];
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
	else if (m)
		throwOnFloor(m);
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= count || !inventory[idx])
		return;

	throwOnFloor(inventory[idx]);

	inventory[idx] = inventory[count - 1];
	inventory[count - 1] = NULL;
	--count;
}

void Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx >= count || !inventory[idx])
		return;

	inventory[idx]->use(target);
}

void Character::cleanFloor()
{
	Floor *current = floorHead;
	while (current)
	{
		Floor *next = current->next;

		if (current->materia)
			delete current->materia;

		delete current;
		current = next;
	}
	floorHead = NULL;
	floorTail = NULL;
}

void Character::throwOnFloor(AMateria *m)
{
	if (m)
	{
		floorTail->materia = m;
		floorTail->next = new Floor();
		floorTail = floorTail->next;
		floorTail->materia = NULL;
		floorTail->next = NULL;
	}
}