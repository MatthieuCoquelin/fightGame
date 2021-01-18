#pragma once
#include "CRanged.h"
class CStaff :
	public CRanged
{
	//methode 
public:
	CStaff();
	CStaff(float manaUsed, float critChance, float damage, std::string name, float life, float attack, float intelligence);
	virtual ~CStaff();

	float getIntelligence();

	//membres
protected:
	float m_manaUsed;
	float m_intelligence;
};

