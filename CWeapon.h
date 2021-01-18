#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>

//liste des armes possibles
typedef enum Weamon_e
{
	None,
	Sword,
	Daguer,
	Bow,
	Staff
}weapon;

class CWeapon
{
	//methodes 
public:
	CWeapon();
	virtual ~CWeapon();
	
	//getteurs / setteurs 
	float getDamage();
	std::string getName();
	float getAttack();
	float getLife();
	void setAttack(float attack);

	//membres
protected:
	std::string m_name;
	float m_damage;
	float m_critChance;
	float m_life;
	float m_attack;
	
};

