#pragma once
#include "CTeam.h"

//lite des equipes
typedef enum Game_e
{
	Team1,
	Team2,
	NUMBER_TEAM
}Game;

class CGame
{
	//methodes
public:
	CGame();
	virtual ~CGame();
	void initGame();
	CCharacter* beFirst();
	CCharacter* randSpeeder(CCharacter* speeder, CCharacter* speederEquality);
	void checkEndGame();
	CCharacter* chooseTarget(int skill);
	CCharacter* chooseTargetInYourTeam();
	CCharacter* chooseTargetInTheOtherTeam();
	std::vector<CCharacter*> chooseTeamTarget(int skill);
	void checkLife(std::vector<CCharacter*> target);
	void checkPoison(CCharacter* character);
	void useSpecialSkill(CCharacter* character);
	void provocationTeam(CCharacter* character, std::vector<CCharacter*> target);
	void repairWeapons(CCharacter* character, std::vector<CCharacter*> target);
	void aimBow(CCharacter* character);
	void healTeamPoison(CCharacter* character, std::vector<CCharacter*> target);
	void healSomeone(CCharacter* character, CCharacter* target);
	void delightWeapon(CCharacter* character, CCharacter* target);
	void poisonTarget(CCharacter* character, CCharacter* target);
	void beStealth(CCharacter* character);
	void mana(CCharacter* character);
	void resetSpeed();
	void loopGame();

	//membres
protected:
	std::vector<CTeam*> m_teams;
	int m_teamOfTheCharacterInAction;
	bool m_endGame;

};
