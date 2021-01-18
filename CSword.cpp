#include "CSword.h"
using namespace std;

//constructeur par defaut 
CSword::CSword()
{
}

//constructeur parametrique 
CSword::CSword(float critChance, float damage, int durability, string name, float attack, float life)
{
	m_critChance = critChance;
	m_damage = damage;
	m_durability = durability;
	m_durabilityMax = durability;
	m_name = name;
	m_state = true;
	m_attack = attack;
	m_life = life;
	m_stateDelight = false;
}

//destructeur 
CSword::~CSword()
{
}


int CSword::randPenalty(int min, int max)
{
	return ((rand() % (max - min + 1)) + min);
}

//methode polymorphique pour mettre a jour la durabilite de l'arme de melee
void CSword::updateDurability()
{
	m_durability -= randPenalty(MIN_DURABILITY, MAX_DURABILITY);
}
