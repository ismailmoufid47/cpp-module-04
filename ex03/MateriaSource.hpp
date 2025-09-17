#pragma once

#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource : public IMateriaSource
{
private:
	AMateria *inventory[4];
	int count;
public:
	MateriaSource();
	MateriaSource(const MateriaSource &other);

	MateriaSource &operator=(const MateriaSource &other);

	virtual ~MateriaSource();

	virtual void learnMateria(AMateria *m);
	virtual AMateria *createMateria(std::string const &type);
};