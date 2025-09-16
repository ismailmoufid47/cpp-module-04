#include <iostream>

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{
	const Animal *animal = new Animal();
	const Animal *dog = new Dog();
	const Animal *cat = new Cat();

	std::cout << std::endl << "Getting types" << std::endl << "---------------------" << std::endl;
	std::cout << "dog type: " << dog->getType() << std::endl;
	std::cout << "cat type: " << cat->getType() << std::endl;

	std::cout << std::endl << "Making sounds" << std::endl << "---------------------" << std::endl;
	std::cout << "cat: ";
	cat->makeSound();
	std::cout << "dog: ";
	dog->makeSound();
	std::cout << "animal: ";
	animal->makeSound();

	std::endl(std::cout);
	delete animal;
	delete dog;
	delete cat;

	std::cout << std::endl << "WrongAnimal tests" << std::endl << "---------------------" << std::endl;
	const WrongAnimal *wrongCat = new WrongCat();

	std::cout << "wrongCat type: " << wrongCat->getType() << std::endl;
	std::cout << "wrongCat sound: ";
	wrongCat->makeSound();
	std::endl(std::cout);
	delete wrongCat;
}
