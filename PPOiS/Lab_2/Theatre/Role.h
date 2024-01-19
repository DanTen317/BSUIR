#pragma once
#include "Actor.h"

class Role
{
private:
	std::string name;
	Actor actor;
public:
	Role(std::string name, Actor actor) : name(name), actor(actor) {};
	bool operator ==(const Role&)const;
};

