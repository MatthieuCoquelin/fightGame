#pragma once
#include "CBow.h"
#include "CStaff.h"
#include "CDagger.h"
#include "CSword.h"
#define MIN_COEF_CHARACTER 0.95f
#define MAX_COEF_CHARACTER 1.05f

//lise des actions possibles 
typedef enum Actions_e
{
	No, //sert uniquement pour initialiser
	AttackWithoutWeapon,
	AttackWithWeapon,
	Scream,
	Repair,
	Aim,
	HealPoison,
	RegenerateMana,
	HealSomeone,
	DelightWeapon,
	Poison,
	Stealth
}Actions;

class CCharacter
{
	//methodes
public:
	CCharacter();
	CCharacter(std::string name, float life, float dodge, float speed, float attack, float defence, float agility, float intelligence);
	virtual ~CCharacter();
	virtual float damageCalculation(CCharacter* target);
	virtual void dodge(float damages);
	float randCoef(float min, float max);
	float dodgeChance();
	void beHurt(float damages);
	virtual void dispCharacter();
	virtual void updateStates();
	CWeapon* readFileWeappon(std::string path);
	std::string selectFile();
	CWeapon* initWeapon();
	virtual void checkWeapon();
	virtual void updateCharacter();
	virtual int choiceMove();

	//assesseurs / muttateurs
	float getDefence();
	float getDodge();
	void setDodge(float dodge);
	void setStateProvocation(int time);
	void setStatePoison(bool state);
	float getLife();
	float getLifeMax();
	void setLife(float life);
	std::string getName();
	void setName(std::string name);
	void setSpeed(float speed);
	CWeapon* getWeapon();
	int getChoiceWeapon();
	float getSpeed();
	float getSpeedInit();
	bool getStatePoison();

	//membres
protected:
	std::string m_name;
	float m_life;
	CWeapon* m_weapon;
	float m_dodge;
	float m_speed;
	float m_attack;
	float m_defence;
	float m_agility;
	float m_intelligence;
	int m_stateProvocation;
	bool m_statePoison;
	float m_lifeMax;
	float m_speedInit;
	int m_choiceWeapon;
	static int m_characterNumber;

};
//fonction qui serviront pour des methodes polymorphiques
void presentCharacter(std::vector<CCharacter*> target);
void updateCharachers(CCharacter* target);
void attackSomeone(CCharacter* assailant, CCharacter* target);
void attackSomeoneWithoutWeapon(CCharacter* assailant, CCharacter* target);
void initCharacter(CCharacter* target);
int action(CCharacter* charcter);