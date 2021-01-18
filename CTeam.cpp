#include "CTeam.h"
#include "CWarrior.h"
#include "CMage.h"
#include "CRogue.h"
#include "CArcher.h"

using namespace std;

//pour initialiser les equipes (changement)
bool CTeam::m_flag = false;

//constructeur par defaut 
CTeam::CTeam()
{
	m_characterInAction = -1;
	initTeam();
}

//destructeur 
CTeam::~CTeam()
{
	for (int i = 0; i < m_characters.size(); i++)
	{
		if (m_characters[i] != NULL)
		{
			delete m_characters[i];
			m_characters[i] = NULL;
		}
	}
}

//mmethode pour initialiser les personnage des fichier txt
CCharacter* CTeam::readFileCharacter(string path)
{
	string character = "";
	std::string name = "";
	float life = 0.0f;
	float dodge = 0.0f;
	float speed = 0.0f;
	float attack = 0.0f;
	float defence = 0.0f;
	float agility = 0.0f;
	float intelligence = 0.0f;
	float block = 0.0f;
	float poisonChance = 0.0f;

	ifstream file(path, ios::in);
	if (file.is_open())
	{
		file >> character;
		if (character == "Mage")
		{
			file >> name >> speed >> attack >> intelligence >> life >> defence >> dodge >> agility;
			return (new CMage(name, life, dodge, speed, attack, defence, agility, intelligence));
		}
		else if (character == "Guerrier")
		{
			file >> name >> speed >> attack >> intelligence >> life >> defence >> dodge >> agility >> block;
			return (new CWarrior(name, life, dodge, speed, attack, defence, agility, intelligence, block));
		}
		else if (character == "Archer")
		{
			file >> name >> speed >> attack >> intelligence >> life >> defence >> dodge >> agility;
			return (new CArcher(name, life, dodge, speed, attack, defence, agility, intelligence));
		}
		else if (character == "Voleur")
		{
			file >> name >> speed >> attack >> intelligence >> life >> defence >> dodge >> agility >> poisonChance;
			return (new CRogue(name, life, dodge, speed, attack, defence, agility, intelligence, poisonChance));
		}
		else
		{
			cout << "Pas d'entourloupe!!!\n";
			return NULL;
		}
	}
	else
	{
		cout << "Impossible d'ouvrir le fichier " << path << ".\n";
		return NULL;
	}
}

//methode pour ger la rotation des fichier lors de l'initialisation des personnages 
void CTeam::initTeam()
{
	if (m_flag == false)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (i == Character1)
				m_characters.push_back(readFileCharacter("team1Character1.txt"));

			if (i == Character2)
				m_characters.push_back(readFileCharacter("team1Character2.txt"));

			if (i == Character3)
				m_characters.push_back(readFileCharacter("team1Character3.txt"));

			initCharacter(m_characters[i]);
		}
	}
	else
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (i == Character1)
				m_characters.push_back(readFileCharacter("team2Character1.txt"));

			if (i == Character2)
				m_characters.push_back(readFileCharacter("team2Character2.txt"));

			if (i == Character3)
				m_characters.push_back(readFileCharacter("team2Character3.txt"));

			initCharacter(m_characters[i]);
		}
	}
	m_flag = true;
	
}

//**************************assesseurs / muttateurs**************************
std::vector<CCharacter*> CTeam::getCharacter()
{
	return m_characters;
}

void CTeam::setCharacterInAction(int character)
{
	m_characterInAction = character;
}

int CTeam::getCharacterInAction()
{
	return m_characterInAction;
}
