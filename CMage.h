#pragma once
#include "CCharacter.h"
#include "CStaff.h"
#define MIN_COEF_MAGE 0.85f
#define MAX_COEF_MAGE 1.00f
#define MANA_MAX 32
class CMage :
	public CCharacter
{
	//methodes
public:
	CMage();
	CMage(std::string name, float life, float dodge, float speed, float attack, float defence, float agility, float intelligence);
	virtual ~CMage();
	virtual float damageCalculation(CCharacter* target);
	virtual void dodge(float damages);
	virtual void dispCharacter();
	virtual void checkWeapon();
	virtual void updateCharacter();
	virtual int choiceMove();
	void regenerateMana();
	void heal(CCharacter* target);
	virtual void updateStates();
	float randMana(int min, int max);
	float randLfe(int min, int max);
	void delight(CCharacter* target);

	//membres
protected:
	float m_mana;
	int m_cooldownHeal;
	int m_cooldownDelight;
};

