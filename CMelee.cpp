#include "CMelee.h"

//constructeuur par defaut
CMelee::CMelee()
{
	m_durability = 0;
	m_durabilityMax = 0;
	m_state = true;
	m_stateDelight = false;
}

//destructeur
CMelee::~CMelee()
{
}

//methode polymorphique pour mettre ajour la durabilite de l'arme d'un personnage
void CMelee::updateDurability()
{
}

//**************************assesseurs / muttateurs**************************
int CMelee::getDurability()
{
	return m_durability;
}

void CMelee::setState(bool state)
{
	m_state = state;
}

bool CMelee::getState()
{
	return m_state;
}

void CMelee::setDurability(int durability)
{
	m_durability = durability;
}

int CMelee::getDurabilityMax()
{
	return m_durabilityMax;
}

void CMelee::setStateDelight(bool state)
{
	m_stateDelight = state;
}

bool CMelee::getStateDelight()
{
	return m_stateDelight;
}