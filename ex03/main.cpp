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

	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter *warrior = new Character("Warrior");

	std::cout << "Equipping 5 materias (max 4 slots):\n";
	for (int i = 0; i < 5; i++)
	{
		AMateria *materia = src->createMateria("ice");
		warrior->equip(materia);
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
	delete src;
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
	src->learnMateria(new Ice()); // Should be ignored

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

void testDirectMateriaUsage()
{
	std::cout << "\n=== DIRECT MATERIA USAGE TEST ===\n";

	Ice *ice = new Ice();
	Cure *cure = new Cure();
	ICharacter *target = new Character("DirectTarget");

	std::cout << "Direct usage:\n";
	ice->use(*target);
	cure->use(*target);

	std::cout << "\nTesting clone:\n";
	AMateria *iceClone = ice->clone();
	AMateria *cureClone = cure->clone();

	iceClone->use(*target);
	cureClone->use(*target);

	delete ice;
	delete cure;
	delete iceClone;
	delete cureClone;
	delete target;
}

int main()
{

	testBasicFunctionality();
	testInventoryLimits();
	testUnequipAndReequip();
	testMateriaSourceLimits();
	testDeepCopy();
	testDirectMateriaUsage();

	std::cout << "\n=== ALL TESTS COMPLETED ===\n";
	std::cout << "Check for memory leaks with valgrind!\n";
}