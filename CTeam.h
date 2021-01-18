#pragma once
#include "CCharacter.h"
#include "CArcher.h"
#include "CMage.h"
#include "CRogue.h"
#include "CWarrior.h"
#include <vector>

//liste de personnages
typedef enum SizeTeam_e
{
	Character1,
	Character2,
	Character3,
	SIZE
}SizeTeam;

class CTeam
{
	//methodes 
public:
	CTeam();
	virtual ~CTeam();
	CCharacter* readFileCharacter(std::string path);
	void initTeam();
	
	//getteurs // setteurs 
	std::vector<CCharacter*> getCharacter();
	void setCharacterInAction(int character);
	int getCharacterInAction();

	//membres
protected:
	std::vector<CCharacter*> m_characters;
	int m_characterInAction;
	static bool m_flag;
};

