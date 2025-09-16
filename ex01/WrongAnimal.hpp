#pragma once

#include <string>

class WrongAnimal
{

protected:
	std::string type;

public:
	WrongAnimal();
	WrongAnimal(const WrongAnimal &other);

	WrongAnimal &operator=(const WrongAnimal &other);

	~WrongAnimal();

	void makeSound() const;

	std::string getType() const;
};