#pragma once
#include "CCharacter.h"
#define MIN_COEF_ARCHER 0.85f
#define MAX_COEF_ARCHER 1.00f
class CArcher :
	public CCharacter
{
	//methodes
public:
	CArcher();
	CArcher(std::string name, float life, float dodge, float speed, float attack, float defence, float agility, float intelligence);
	virtual ~CArcher();
	void aim();
	void hillPoison(std::vector<CCharacter*> target);
	virtual float damageCalculation(CCharacter* target);
	virtual void dodge(float damages);
	virtual void dispCharacter();
	virtual void updateStates();
	virtual void checkWeapon();
	virtual void updateCharacter();
	virtual int choiceMove();

	//membres
protected:
	int m_hillNumber;
	bool m_statAim;
};

