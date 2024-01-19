#include "Role.h"

bool Role::operator==(const Role& second_role) const
{
	if (this->actor == second_role.actor)
		if (this->name == second_role.name)
			return true;
	return false;
}
