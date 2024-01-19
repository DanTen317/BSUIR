#include "Actor.h"

Actor::Actor(std::string name, int age, std::string rank)
	: rank(rank), Human(name, age) {}

void Actor::print() const
{
	Human::print();
	std::cout << "is an actor" << std::endl <<rank<<std::endl;
}

bool Actor::operator==(const Actor& second_actor) const
{
	if (this->name == second_actor.name)
		if (this->age == second_actor.age)
			if (this->rank == second_actor.rank)
				return true;
	return false;
}
