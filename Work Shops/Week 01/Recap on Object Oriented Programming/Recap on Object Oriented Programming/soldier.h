#pragma once

#include <iostream>

class soldier
{
public:
	soldier(const char* name);
	~soldier();

	bool isDead();
	void printHealth();
	const char* getName();
	void reduceHealth(float damage);

	void attack(soldier & enemy);

private:
	std::string m_name;
	int m_weaponDamage;
	int m_health;

	void shoot(soldier &enemy);
};

