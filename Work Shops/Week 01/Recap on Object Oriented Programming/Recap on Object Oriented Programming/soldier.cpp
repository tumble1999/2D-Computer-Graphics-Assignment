#include "soldier.h"

soldier::soldier(const char * name)
{
	m_health = 100;
	m_name = name;
	m_weaponDamage = 10;
}

soldier::~soldier()
{}

bool soldier::isDead()
{
	return m_health <= 0;
}

void soldier::printHealth()
{
	std::cout << m_name.c_str() << "'s health is " << m_health << std::endl;
}

void soldier::shoot(soldier & enemy)
{
	int shotDamage = rand() % m_weaponDamage;
	std::cout << getName() << " shoots " << enemy.getName();
		
	if (shotDamage > 0 )
	{
		std::cout << " by " << shotDamage << " damage" << std::endl;
	}
	else
	{
		std::cout << " and misses" << std::endl;
	}

//	enemy.reduceHealth(shotDamage);
}

const char * soldier::getName()
{
	return m_name.c_str();
}

void soldier::reduceHealth(float damage)
{
//	m_health -= damage;
}

void soldier::attack(soldier & enemy)
{
	shoot(enemy);
}
