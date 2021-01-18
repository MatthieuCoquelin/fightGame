#include "CGame.h"
using namespace std;

//constructeur par defaut 
CGame::CGame()
{
	m_teamOfTheCharacterInAction = -1;
	m_endGame = false;
}

//destructeur 
CGame::~CGame()
{
	for (int i = 0; i < m_teams.size(); i++)
	{
		if (m_teams[i] != NULL)
		{
			delete m_teams[i];
			m_teams[i] = NULL;
		}
	}
}

//methode pour pour creer les equipes 
void CGame::initGame()
{
	cout << "Determinons pour chaque personnage si ils doivent avoir une arme.\n";
	for (int i = 0; i < NUMBER_TEAM; i++)
	{
		m_teams.push_back(new CTeam());
	}
}

//methode pour determiner le personnage qui joue 
CCharacter* CGame::beFirst()
{
	int i = 0, j = 0;
	float min = 0.0f;
	
	CCharacter* speeder = m_teams[i]->getCharacter()[j];
	CCharacter* speederEquality = NULL;
	min =m_teams[i]->getCharacter()[j]->getSpeed();
	m_teamOfTheCharacterInAction = Team1;
	m_teams[i]->setCharacterInAction(Character1);
	
	j++;

	for (i = 0; i < m_teams.size(); i++)
	{
		for (j; j < m_teams[i]->getCharacter().size(); j++)
		{
			
			if (m_teams[i]->getCharacter()[j]->getSpeed() < min)
			{
				min = m_teams[i]->getCharacter()[j]->getSpeed();
				speeder = m_teams[i]->getCharacter()[j];

				m_teamOfTheCharacterInAction = i;
				m_teams[i]->setCharacterInAction(j);
			}
			if (m_teams[i]->getCharacter()[j]->getSpeed() == min)
			{
				speederEquality = m_teams[i]->getCharacter()[j];
				speeder = randSpeeder(speeder, speederEquality);
				if (speeder == speederEquality)
				{
					m_teamOfTheCharacterInAction = i;
					m_teams[i]->setCharacterInAction(j);
				}
			}
			
		}
		j = 0;
	}

	for (i = 0; i < m_teams.size(); i++)
	{
		for (j = 0; j < m_teams[i]->getCharacter().size(); j++)
		{
			m_teams[i]->getCharacter()[j]->setSpeed(m_teams[i]->getCharacter()[j]->getSpeed() - speeder->getSpeed());
		}
		
	}
	cout << "C'est au joueur " << (m_teamOfTheCharacterInAction + 1) << " de jouer avec le perso " << (m_teams[m_teamOfTheCharacterInAction]->getCharacterInAction() + 1) << " qui s'appelle " << speeder->getName() << endl;
	
	return speeder;
}

CCharacter* CGame::randSpeeder(CCharacter* speeder, CCharacter* speederEquality)
{
	int randomValue = rand() % 2;
	
	if (randomValue == 1)
		return speederEquality;
	return speeder;
}

//methode pour veirfier la fin de jeu
void CGame::checkEndGame()
{
	if (m_teams[Team1]->getCharacter().size() == 0)
	{
		cout << "Equipe 2 gagne.\n" << endl;
		m_endGame = true;
		return;
	}
	if (m_teams[Team2]->getCharacter().size() == 0)
	{
		cout << "Equipe 1 gagne.\n" << endl;
		m_endGame = true;
		return;
	}
}

//methode pour choisir une cible (ennemie ou alie)
CCharacter* CGame::chooseTarget(int skill)
{
	CCharacter* target = NULL; 
	
	switch (skill)
	{
	case No:
		target = chooseTargetInTheOtherTeam();
		break;
	case AttackWithoutWeapon:
		target = chooseTargetInTheOtherTeam();
		break;
	case AttackWithWeapon:
		target = chooseTargetInTheOtherTeam();
		break;
	case HealSomeone:
		target = chooseTargetInYourTeam();
		break;
	case Poison:
		target = chooseTargetInTheOtherTeam();
		break;
	case DelightWeapon:
		return chooseTargetInYourTeam();
		break;
	default:
		target = chooseTargetInTheOtherTeam();
		break;
	}
	return target;
}

//methode pour choisir une cible parmis les alies 
CCharacter* CGame::chooseTargetInYourTeam()
{
	int choice = -1;

	cout << "Sur quel perso de votre equipe utilisez vous cette comptence?\n";
	cout << "1. Perso 1\n2. Perso 2\n3. Perso 3\n";
	cin >> choice;

	switch (choice)
	{
	case (Character1 + 1):
		return m_teams[m_teamOfTheCharacterInAction]->getCharacter()[Character1];
		break;
	case (Character2 + 1):
		if (m_teams[m_teamOfTheCharacterInAction]->getCharacter().size() < 2)
		{
			cout << "Au moins un personnage est mort. La cible sera donc le perso 1.\n";
			m_teams[m_teamOfTheCharacterInAction]->getCharacter()[Character1];
		}
		return m_teams[m_teamOfTheCharacterInAction]->getCharacter()[Character2];
		break;
	case (Character3 + 1):
		if (m_teams[m_teamOfTheCharacterInAction]->getCharacter().size() < 3)
		{
			cout << "Au moins un personnage est mort. La cible sera donc le perso 1.\n";
			m_teams[m_teamOfTheCharacterInAction]->getCharacter()[Character1];
		}
		return m_teams[m_teamOfTheCharacterInAction]->getCharacter()[Character3];
		break;
	default:
		cout << "A defaut vous utilisez cette competence sur vous.\n";
		return m_teams[m_teamOfTheCharacterInAction]->getCharacter()[m_teams[m_teamOfTheCharacterInAction]->getCharacterInAction()];
		break;
	}
}

//method pour choisir une cibl parmi les ennemis 
CCharacter* CGame::chooseTargetInTheOtherTeam()
{
	int choice = -1;

	cout << "Sur quel perso de l'equipe adverse utilisez vous cette comptence?\n";
	cout << "1. Perso 1\n2. Perso 2\n3. Perso 3\n";
	cin >> choice;

	switch (choice)
	{
	case (Character1 + 1):
		return m_teams[1 - m_teamOfTheCharacterInAction]->getCharacter()[Character1];
		break;
	case(Character2 + 1):
		if (m_teams[1 - m_teamOfTheCharacterInAction]->getCharacter().size() < 2)
		{
			cout << "Au moins un personnage est mort. La cible sera donc le perso 1.\n";
			m_teams[1 - m_teamOfTheCharacterInAction]->getCharacter()[Character1];
		}
		return m_teams[1 - m_teamOfTheCharacterInAction]->getCharacter()[Character2];
		break;
	case (Character3 + 1):
		if (m_teams[1 - m_teamOfTheCharacterInAction]->getCharacter().size() < 3)
		{
			cout << "Au moins un personnage est mort. La cible sera donc le perso 1.\n";
			m_teams[1 - m_teamOfTheCharacterInAction]->getCharacter()[Character1];
		}
		return m_teams[1 - m_teamOfTheCharacterInAction]->getCharacter()[Character3];
		break;
	default:
		cout << "A defaut vous utilisez cette competence sur votre homologue.\n";
		return m_teams[m_teamOfTheCharacterInAction]->getCharacter()[1 - m_teams[m_teamOfTheCharacterInAction]->getCharacterInAction()];
		break;
	}
}

//methode pour determiner l'equipe cible 
vector<CCharacter*> CGame::chooseTeamTarget(int skill)
{
	switch (skill)
	{
	case Scream:
		return m_teams[1 - m_teamOfTheCharacterInAction]->getCharacter();
		break;
	case Repair:
		return m_teams[m_teamOfTheCharacterInAction]->getCharacter();
		break;
	case HealPoison:
		return m_teams[m_teamOfTheCharacterInAction]->getCharacter();
		break;
	default:
		cout << "voici une equipe...\n";
		return m_teams[m_teamOfTheCharacterInAction]->getCharacter();
		break;
	}
}

//methode pour verifier les perso en vie 
void CGame::checkLife(vector<CCharacter*> target)
{
	for (int i = 0; i < target.size(); i++)
	{
		if (target[i]->getLife() <= 0.0f)
		{
			cout << target[i]->getName() << " meurt.\n";
			delete target[i];
			target[i] = NULL;
			target.erase(target.begin() + i);
		}
	}
}

//methode pour verifier si le personnage est empoisonner et gerer sa vie 
void CGame::checkPoison(CCharacter* character)
{
	if (character->getStatePoison() == true)
	{
		cout << character->getName() << " perd de la vie a cause du poison.\n";
		character->setLife(character->getLife() / 12.0f);
	}
}

//methode pour "choisir" l'action d'un perso
void CGame::useSpecialSkill(CCharacter* character)
{
	int skill = action(character);
	switch (skill)
	{
	case No:
		attackSomeoneWithoutWeapon(character, chooseTarget(skill));
		break;
	case AttackWithoutWeapon:
		attackSomeoneWithoutWeapon(character, chooseTarget(skill));
		break;
	case AttackWithWeapon:
		attackSomeone(character, chooseTarget(skill));
		break;
	case Scream:
		provocationTeam(character, chooseTeamTarget(skill));
		break;
	case Repair:
		repairWeapons(character, chooseTeamTarget(skill));
		break;
	case Aim:
		aimBow(character);
		break;
	case HealPoison:
		healTeamPoison(character, chooseTeamTarget(skill));
		break;
	case RegenerateMana:
		mana(character);
		break;
	case HealSomeone:
		healSomeone(character, chooseTarget(skill));
		break;
	case DelightWeapon:
		delightWeapon(character, chooseTarget(skill));
		break;
	case Poison:
		poisonTarget(character, chooseTarget(skill));
		break;
	case Stealth:
		beStealth(character);
		break;

	default:
		cout << "A deffaut votre personnage attaque a mains nues\n";
		attackSomeoneWithoutWeapon(character, chooseTarget(skill));
		break;
	}

}
//**************************dynamicCasts**************************
void CGame::provocationTeam(CCharacter* character, std::vector<CCharacter*> target)
{
	dynamic_cast<CWarrior*>(character)->provocation(target);
}

void CGame::repairWeapons(CCharacter* character, std::vector<CCharacter*> target)
{
	dynamic_cast<CWarrior*>(character)->repair(target);
}

void CGame::aimBow(CCharacter* character)
{
	dynamic_cast<CArcher*>(character)->aim();
}

void CGame::healTeamPoison(CCharacter* character, std::vector<CCharacter*> target)
{
	dynamic_cast<CArcher*>(character)->hillPoison(target);
}

void CGame::healSomeone(CCharacter* character, CCharacter* target)
{
	dynamic_cast<CMage*>(character)->heal(target);
}

void CGame::delightWeapon(CCharacter* character, CCharacter* target)
{
	dynamic_cast<CMage*>(character)->delight(target);
}

void CGame::poisonTarget(CCharacter* character, CCharacter* target)
{
	dynamic_cast<CRogue*>(character)->poison(target);
}

void CGame::beStealth(CCharacter* character)
{
	dynamic_cast<CRogue*>(character)->stealth();
}

void CGame::mana(CCharacter* character)
{
	dynamic_cast<CMage*>(character)->regenerateMana();
}

//methode pour reinitialiser la vitesse du perso qui vient de jouer
void CGame::resetSpeed()
{
	m_teams[m_teamOfTheCharacterInAction]->getCharacter()[m_teams[m_teamOfTheCharacterInAction]->getCharacterInAction()]->setSpeed(m_teams[m_teamOfTheCharacterInAction]->getCharacter()[m_teams[m_teamOfTheCharacterInAction]->getCharacterInAction()]->getSpeedInit());
}

//boucle de jeu
void CGame::loopGame()
{
	CCharacter* character = NULL;
	int i = 0;
	initGame();

	for ( i = 0; i < NUMBER_TEAM; i++)
	{
		presentCharacter(m_teams[i]->getCharacter());
	}

	do
	{
		character = beFirst();
		checkPoison(character);
		useSpecialSkill(character);
		updateCharachers(character);
		resetSpeed();

		for ( i = 0; i < NUMBER_TEAM; i++)
		{
			checkLife(m_teams[i]->getCharacter());
			cout << "\nTeam " << (i + 1) << "\n";
			presentCharacter(m_teams[i]->getCharacter());
		}

		checkEndGame();
	} 
	while (m_endGame == false);
}

