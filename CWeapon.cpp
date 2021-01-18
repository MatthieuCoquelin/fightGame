#include "CWeapon.h"

//constructeur par defaut 
CWeapon::CWeapon()
{
	m_name = "";
	m_critChance = 0.0f;
	m_damage = 0.0f;
}

//destructeur
CWeapon::~CWeapon()
{
}

//**************************assesseurs / muttateurs**************************
float CWeapon::getDamage()
{
	return m_damage;
}

std::string CWeapon::getName()
{
	return m_name;
}

float CWeapon::getAttack()
{
	return m_attack;
}

float CWeapon::getLife()
{
	return m_life;
}

void CWeapon::setAttack(float attack)
{
	m_attack = attack;
}

