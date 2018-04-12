#pragma once
#include "soldier.h"
class grenadier :
	public soldier
{
public:

	grenadier(const char* name);
	~grenadier();

	void attack(soldier & enemy);
private:
	int m_grenadeDamage;

	void throw_genade(soldier& enemy);
};

