#include "CStaff.h"

using namespace std;

//constructeur par defaut 
CStaff::CStaff()
{
	m_manaUsed = 0.0f;
	m_intelligence = 0.0f;
}

//constructeur parametrique 
CStaff::CStaff(float manaUsed, float critChance, float damage, string name, float life, float attack, float intelligence)
{
	m_manaUsed = manaUsed;
	m_critChance = critChance;
	m_damage = damage;
	m_name = name;
	m_intelligence = intelligence;
	m_life = life;
	m_attack = attack;
}

//destructeur 
CStaff::~CStaff()
{
}

//getteur
float CStaff::getIntelligence()
{
	return m_intelligence;
}
