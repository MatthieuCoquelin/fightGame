#pragma once
#include "CWeapon.h"
class CMelee :
	public CWeapon
{
	//methodes
public:
	CMelee();
	virtual ~CMelee();
	virtual void updateDurability() = 0;

	//assesseurs / muttateurs
	int getDurability();
	void setState(bool state);
	bool getState();
	void setDurability(int durability);
	int getDurabilityMax();
	bool getStateDelight();
	void setStateDelight(bool state);

	//membres
protected:
	int m_durability;
	int m_durabilityMax;
	bool m_state;
	bool m_stateDelight;
};

