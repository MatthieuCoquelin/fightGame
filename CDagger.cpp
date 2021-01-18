#include "CDagger.h"

//constructeur par defaut 
CDagger::CDagger()
{
	m_agility = 0.0f;
	m_defence = 0.0f;
}

//constructeur parametrique 
CDagger::CDagger(float critChance, float damage, int durability, std::string name, float life, float defence, float attack, float agility)
{
	m_critChance = critChance;
	m_damage = damage;
	m_durability = durability;
	m_durabilityMax = durability;
	m_name = name;
	m_life = life;
	m_defence = defence;
	m_attack = attack;
	m_agility = agility;
	m_state = true;
	m_stateDelight = false;
}

//destructeur
CDagger::~CDagger()
{
}

//methode polymorphique pour mettre a jour la durabilite de l'arme de melee
void CDagger::updateDurability()
{
	m_durability -= PENALTY;
}

//**************************assesseurs / muttateurs**************************
float CDagger::getAgility()
{
	return m_agility;
}

float CDagger::getDefence()
{
	return m_defence;
}

