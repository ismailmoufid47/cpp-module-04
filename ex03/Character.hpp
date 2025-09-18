#pragma once

#include "ICharacter.hpp"
#include "AMateria.hpp"

struct Floor
{
	AMateria *materia;
	Floor *next;

	Floor() : materia(NULL), next(NULL) {}
};

class Character : public ICharacter
{
private:
	std::string name;
	AMateria *inventory[4];
	int count;


public:
	Character();
	Character(const std::string &name);
	Character(const Character &other);

	Character &operator=(const Character &other);

	~Character();

	std::string const &getName() const;
	void equip(AMateria *m);
	void unequip(int idx);
	void use(int idx, ICharacter &target);

static Floor *floorHead;
static Floor *floorTail;
static void throwOnFloor(AMateria *m);
static void cleanFloor();
};