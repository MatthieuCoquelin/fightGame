#pragma once
#include "CMelee.h"
#define MAX_DURABILITY 5
#define MIN_DURABILITY 2
class CSword :
	public CMelee
{
	//methodes 
public:
	CSword();
	CSword(float critChance, float damage, int durability, std::string name, float attack, float life);
	virtual ~CSword();
	int randPenalty(int min, int max);
	void updateDurability();

protected:

};

