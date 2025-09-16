#include <iostream>

#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	const int size = 10;
	Animal *animals[size];

	for (int i = 0; i < size; i++)
	{
		if (i < size / 2)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}

	for (int i = 0; i < size; i++)
		animals[i]->makeSound();

	for (int i = 0; i < size; i++)
		delete animals[i];
}
