#pragma once
#include "CCharacter.h"
#define MIN_COEF_WARRIOR 0.85f
#define MAX_COEF_WARRIOR 1.00f
class CWarrior :
	public CCharacter
{
	//methodes 
public:
	CWarrior();
	CWarrior(std::string name, float life, float dodge, float speed, float attack, float defence, float agility, float intelligence, float block);
	virtual ~CWarrior();
	virtual float damageCalculation(CCharacter* target);
	virtual void dodge(float damages);
	virtual void dispCharacter();
	void provocation(std::vector<CCharacter*> target);
	virtual void updateStates();
	virtual void checkWeapon();
	virtual void updateCharacter();
	virtual int choiceMove();
	int randProvocation(int min, int max);
	void repair(std::vector<CCharacter*> target);
	int randDurability(int min, int max);

	//membres 
protected:
	float m_block;
	int m_cooldownScream;

};

