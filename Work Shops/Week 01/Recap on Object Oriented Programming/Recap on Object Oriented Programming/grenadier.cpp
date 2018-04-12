#include "grenadier.h"

grenadier::grenadier(const char * name) : soldier(name)
{
	m_grenadeDamage = 20;
}


grenadier::~grenadier()
{}

void grenadier::attack(soldier & enemy)
{
	throw_genade(enemy);
}


void grenadier::throw_genade(soldier& enemy)
{
	int grenadeDamage = rand() % m_grenadeDamage;
	std::cout << getName() << " threw a granade at " << enemy.getName();

	if (grenadeDamage > 0)
	{
		std::cout << " by " << grenadeDamage << " damage" << std::endl;
	}
	else
	{
		std::cout << " and misses" << std::endl;
	}

//	enemy.reduceHealth(grenadeDamage);


	int devisor = 2;
	int recoilDamage = rand() % (m_grenadeDamage / devisor );

	if (recoilDamage > 0)
	{
		std::cout << getName() << " recived " << recoilDamage << " damage for being with in range of the explosion" << std::endl;
//		reduceHealth(recoilDamage);
	}
}
