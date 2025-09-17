#include "MateriaSource.hpp"

#include <iostream>

MateriaSource::MateriaSource() : count(0){}

MateriaSource::MateriaSource(const MateriaSource &other) : count(0)
{
	*this = other;
}

MateriaSource &MateriaSource::operator=(const MateriaSource &other)
{
	if (this != &other)
	{
		for (int i = 0; i < count; i++)
			delete inventory[i];

		count = other.count;

		for (int i = 0; i < count; i++)
			inventory[i] = other.inventory[i]->clone();
	}
	return *this;
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < count; i++)
		delete inventory[i];
}

void MateriaSource::learnMateria(AMateria *m)
{
	if (count < 4 && m)
	{
		inventory[count] = m;
		count++;
	}
	else if (m)
	{
		std::cout << "MateriaSource: Inventory full, cannot learn more materia" << std::endl;
		delete m;
	}
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < count; i++)
		if (inventory[i]->getType() == type)
			return inventory[i]->clone();

	std::cout << "MateriaSource: Unknown materia type '" << type << "'" << std::endl;
	return nullptr;
}