#pragma once
#include "CRanged.h"
class CBow :
	public CRanged
{
	//methodes
public:
	CBow();
	CBow(int arrowNumber, float critChance, float damage, std::string name, float attack, float life);
	virtual ~CBow();

	//membres
protected:
	int m_arrowNumber;

};

