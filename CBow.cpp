#include "CBow.h"
using namespace std;

//constructeur par defaut
CBow::CBow()
{
	m_arrowNumber = 0;
}

//constructeur parametrique
CBow::CBow(int arrowNumber, float critChance, float damage, string name, float attack, float life)
{
	m_arrowNumber = arrowNumber;
	m_critChance = critChance;
	m_damage = damage;
	m_name = name;
	m_attack = attack;
	m_life = life;
}

//destructeur
CBow::~CBow()
{
}

