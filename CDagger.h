#pragma once
#include "CMelee.h"
#define PENALTY 1
class CDagger :
	public CMelee
{
	//methodes
public:
	CDagger();
	CDagger(float critChance, float damage, int durability, std::string name, float life, float defence, float attack, float agility);
	virtual ~CDagger();
	void updateDurability();

	float getAgility();
	float getDefence();

	//membres
protected:
	float m_agility;
	float m_defence;

};
