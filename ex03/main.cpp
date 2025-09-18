#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include <iostream>

void testBasicFunctionality()
{
	std::cout << "\n=== BASIC FUNCTIONALITY TEST ===\n";

	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter *me = new Character("Alice");
	AMateria *tmp;

	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter *bob = new Character("Bob");

	std::cout << "Using materias:\n";
	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;
}

void testInventoryLimits()
{
	std::cout << "\n=== INVENTORY LIMITS TEST ===\n";

	MateriaSource src;
	src.learnMateria(new Ice());
	src.learnMateria(new Cure());

	ICharacter *warrior = new Character("Warrior");

	std::cout << "Equipping 5 materias (max 4 slots):\n";
	for (int i = 0; i < 5; i++)
	{
		warrior->equip(src.createMateria("ice"));
		std::cout << "Equipped materia " << i + 1 << "\n";
	}

	ICharacter *target = new Character("Target");
	std::cout << "\nUsing all slots:\n";
	for (int i = 0; i < 6; i++)
	{
		std::cout << "Slot " << i << ": ";
		warrior->use(i, *target);
	}

	delete target;
	delete warrior;
}

void testUnequipAndReequip()
{
	std::cout << "\n=== UNEQUIP/REEQUIP TEST ===\n";

	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter *mage = new Character("Mage");
	ICharacter *dummy = new Character("Dummy");

	AMateria *ice = src->createMateria("ice");
	AMateria *cure = src->createMateria("cure");
	mage->equip(ice);
	mage->equip(cure);

	std::cout << "Before unequip:\n";
	mage->use(0, *dummy);
	mage->use(1, *dummy);

	std::cout << "\nUnequipping slot 0...\n";
	mage->unequip(0);

	std::cout << "After unequip:\n";
	mage->use(0, *dummy);
	mage->use(1, *dummy);
	std::cout << "\nRe-equipping a new ice materia...\n";
	AMateria *newIce = src->createMateria("ice");
	mage->equip(newIce);
	std::cout << "After re-equip:\n";
	mage->use(0, *dummy);
	mage->use(1, *dummy);

	delete dummy;
	delete mage;
	delete src;
}

void testMateriaSourceLimits()
{
	std::cout << "\n=== MATERIA SOURCE LIMITS TEST ===\n";

	MateriaSource *src = new MateriaSource();

	std::cout << "Learning 5 materias (max 4):\n";
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(new Ice());

	std::cout << "Testing unknown materia type:\n";
	AMateria *unknown = src->createMateria("fire");
	if (unknown)
	{
		std::cout << "Created fire materia\n";
		delete unknown;
	}
	else
		std::cout << "Fire materia not found (expected)\n";

	delete src;
}

void testDeepCopy()
{
	std::cout << "\n=== DEEP COPY TEST ===\n";

	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());

	Character original("Original");
	AMateria *materia = src->createMateria("ice");
	original.equip(materia);

	std::cout << "Original character equipped\n";

	Character copy1(original);
	std::cout << "Copy constructor created\n";

	Character copy2("Temp");
	copy2 = original;
	std::cout << "Assignment operator used\n";

	ICharacter *target = new Character("Target");

	std::cout << "\nTesting that copies are independent:\n";
	std::cout << "Original: ";
	original.use(0, *target);
	std::cout << "Copy1: ";
	copy1.use(0, *target);
	std::cout << "Copy2: ";
	copy2.use(0, *target);
	delete target;
	delete src;
}

int main()
{

	testBasicFunctionality();
	testDeepCopy();

	testInventoryLimits();
	testMateriaSourceLimits();

	testUnequipAndReequip();

	std::cout << "\n=== ALL TESTS COMPLETED ===\n";
	Character::cleanFloor();
	// while (true) { }
}