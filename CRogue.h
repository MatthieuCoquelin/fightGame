#pragma once
#include "CCharacter.h"
#define MIN_COEF_ROGUE 0.85f
#define MAX_COEF_ROGUE 1.00f
class CRogue :
	public CCharacter
{
public:
	CRogue();
	CRogue(std::string name, float life, float dodge, float speed, float attack, float defence, float agility, float intelligence, float poisonChance);
	virtual ~CRogue(); 
	virtual float damageCalculation(CCharacter* target);
	virtual void dodge(float damages);
	virtual void dispCharacter();
	virtual void checkWeapon();
	virtual void updateCharacter();
	virtual int choiceMove();
	void poison(CCharacter* target);
	virtual void updateStates();
	float poisonChance();
	void stealth();
	int randStealth(int min, int max);

protected:
	float m_poisonChance;
	int m_cooldownStealth;
	int m_stateStealth;
};

