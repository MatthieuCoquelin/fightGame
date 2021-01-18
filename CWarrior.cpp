#include "CWarrior.h"
#include "CSword.h"
#include "CDagger.h"
using namespace std;

//constructeuur par defaut 
CWarrior::CWarrior()
{
	m_weapon = NULL;
	m_name = "";
	m_life = 0.0f;
	m_dodge = 0.0f;
	m_speed = 0.0f;
	m_attack = 0.0f;
	m_defence = 0.0f;
	m_agility = 0.0f;
	m_intelligence = 0.0f;
	m_block = 0.0f;
	m_lifeMax = 0.0f;
	m_speedInit = 0.0f;
	m_cooldownScream = 0;
	m_stateProvocation = 0;
	m_statePoison = false;
	m_choiceWeapon = false;
	
}

//constructeur parametrique
CWarrior::CWarrior(string name, float life, float dodge, float speed, float attack, float defence, float agility, float intelligence, float block)
{
	m_choiceWeapon = None;
	m_weapon = initWeapon();
	m_name = name;
	m_life = life;
	m_dodge = dodge;
	m_speed = speed;
	m_attack = attack;
	m_defence = defence;
	m_agility = agility;
	m_intelligence = intelligence;
	m_block = block;
	m_lifeMax = life;
	m_speedInit = speed;
	m_cooldownScream = 0;
	m_stateProvocation = 0;
	m_statePoison = false;
}

//destructeur 
CWarrior::~CWarrior()
{
	m_characterNumber--;
	if (m_weapon != NULL)
		delete m_weapon;
}

//methode polymorphique pour calculer lles degats d'un guerrier 
float CWarrior::damageCalculation(CCharacter* target)
{
	return ((7.0f * (m_attack + m_weapon->getDamage()) * randCoef(MIN_COEF_WARRIOR, MAX_COEF_WARRIOR)) / target->getDefence());
}

//methode polymorphique pour gerer l'esquive d'un guerrier... et la faculter de parer aussi
void CWarrior::dodge(float damages)
{
	int choix = 0;

	cout << "Que dois faire " << m_name << "?\n";
	cout << "Esquiver ou parer ?\n0. esquiver\n1. parer\n";
	cin >> choix;

	if (choix == 1)
	{
		if (m_choiceWeapon == Sword)
		{
			cout << m_name << " tente de parer l'attaque de son adversaire...\n";
			this->setDodge(this->getDodge() + m_block);
		}
			
		else
			cout << "\nNon!!! Il faut une epee!\n" << endl;
	}
	cout << "\n";

	if (this->dodgeChance() > this->getDodge())
	{
		this->beHurt(damages);
		cout << m_name << " prend " << damages << " degats\n" << endl;
	}
		
	else
		cout << "Miss...\n" << endl;
}

//methode polymorphique pour presenter un guerrier 
void CWarrior::dispCharacter()
{
	cout << "Nom:\t\t\t" << m_name << "\n";
	cout << "Attaque:\t\t" << m_attack << "\n";
	cout << "Vie:\t\t\t" << m_life << "\n";
	cout << "Agilite:\t\t" << m_agility << "\n";
	cout << "Esquive:\t\t" << m_dodge << "\n";
	cout << "Arme:\t\t\t" << m_choiceWeapon << "\n";
	cout << "Defence:\t\t" << m_defence << "\n";
	cout << "Inteligence:\t\t" << m_intelligence << "\n";
	cout << "Vitesse:\t\t" << m_speed << "\n";
	cout << "CD Provocation:\t\t" << m_cooldownScream << "\n";
	cout << "Poison:\t\t\t" << m_statePoison << "\n";
	cout << "Provocation:\t\t" << m_stateProvocation << "\n";
	if (m_weapon != NULL)
	{
		if (m_choiceWeapon == Sword)
		{
			cout << "EtatArme:\t\t" << dynamic_cast<CSword*>(m_weapon)->getDurability() << "\n";
		}
		if (m_choiceWeapon == Daguer)
		{
			cout << "EtatArme:\t\t" << dynamic_cast<CDagger*>(m_weapon)->getDurability() << "\n";
		}
	}
	cout << "\n";
}

//methode pour provoquer l'equipe ennemie
void CWarrior::provocation(vector<CCharacter*> target)
{
	cout << m_name << " provoque l'equipe adverse.\n";
	for (int i = 0; i < target.size(); i++)
	{
		target[i]->setStateProvocation(this->randProvocation(1, 2));
		m_cooldownScream = 4;
	}
}

//methode polymorphique pour mettre a jour les stats d'un guerrier 
void CWarrior::updateStates()
{
	if (m_stateProvocation > 0)
		m_stateProvocation--;

	if (m_cooldownScream > 0)
		m_cooldownScream--;

	if (m_choiceWeapon == Sword)
	{
		if (dynamic_cast<CSword*>(m_weapon)->getDurability() < 0)
			dynamic_cast<CSword*>(m_weapon)->setState(false);
	}
	if (m_choiceWeapon == Daguer)
	{
		if (dynamic_cast<CDagger*>(m_weapon)->getDurability() < 0)
			dynamic_cast<CDagger*>(m_weapon)->setState(false);
	}
}

// methode polymorphique pour verifier que l'arme tenue par le guerrier est correcte 
void CWarrior::checkWeapon()
{
	if (m_choiceWeapon == Staff || m_choiceWeapon == Bow)
	{
		cout << "L'arme de " << m_name << " n'est pas correcte. On lui la retire.\n";
		delete m_weapon;
		m_weapon = NULL;
		m_choiceWeapon = None;
	}
}

// methode polymorphique pour modifier les stats d'un guerrier en fonction de son arme 
void CWarrior::updateCharacter()
{
	if (m_weapon != NULL)
	{
		if (m_choiceWeapon == Daguer)
		{
			m_attack += m_weapon->getAttack();
			m_life += m_weapon->getLife();
			m_agility += dynamic_cast<CDagger*>(m_weapon)->getAgility();
			m_defence += dynamic_cast<CDagger*>(m_weapon)->getDefence();
		}
		if (m_choiceWeapon == Sword)
		{
			m_attack += m_weapon->getAttack();
			m_life += m_weapon->getLife();
		}
	}
}

//methode polymorphique pour choisir l'actiion d'un guerrier 
int CWarrior::choiceMove()
{
	if (m_stateProvocation > 0)
	{
		cout << "Sous la provocation " << m_name << " attaque avec son arme.\n";
		return AttackWithWeapon;
	}

	int choice = No;
	cout << "Que voulez vous faire?\n";
	cout << "1. Attaquer sans arme\n2. Attaquer avec une arme\n3. Hurler\n4. reparer l'arme d'un coequipier.\n" << endl;
	cin >> choice;

	switch (choice)
	{
	case 1:
		return AttackWithoutWeapon;
		break;
	case 2:
		return AttackWithWeapon;
		break;
	case 3:
		return Scream;
		break;
	case 4:
		return Repair;
		break;
	default:
		cout << "Vous avez fait le mauvait choix. Votre perso attaque a mains nues\n";
		return AttackWithoutWeapon;
		break;
	}
}

int CWarrior::randProvocation(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}

//methode pour reparer les armes de melee de son equipe 
void CWarrior::repair(vector<CCharacter*> target)
{
	for ( int i = 0; i < target.size(); i++)
	{
		if (target[i]->getWeapon() != NULL)
		{
			if (target[i]->getChoiceWeapon() == Daguer)
			{
				cout << m_name << " repare l'arme de " << target[i]->getName() << ".\n";
				if (dynamic_cast<CDagger*>(target[i]->getWeapon())->getState() == false)
				{
					dynamic_cast<CDagger*>(target[i]->getWeapon())->setState(true);
					dynamic_cast<CDagger*>(target[i]->getWeapon())->setDurability(1);
				}
				else
				{
					dynamic_cast<CDagger*>(target[i]->getWeapon())->setDurability(dynamic_cast<CDagger*>(target[i]->getWeapon())->getDurability() + randDurability(3, 15));
					if (dynamic_cast<CDagger*>(target[i]->getWeapon())->getDurability() > dynamic_cast<CDagger*>(target[i]->getWeapon())->getDurabilityMax())
					{
						dynamic_cast<CDagger*>(target[i]->getWeapon())->setDurability(dynamic_cast<CDagger*>(target[i]->getWeapon())->getDurabilityMax());
					}
				}
			}
			if (target[i]->getChoiceWeapon() == Sword)
			{
				cout << m_name << " repare l'arme de " << target[i]->getName() << ".\n";
				if (dynamic_cast<CSword*>(target[i]->getWeapon())->getState() == false)
				{
					dynamic_cast<CSword*>(target[i]->getWeapon())->setState(true);
					dynamic_cast<CSword*>(target[i]->getWeapon())->setDurability(1);
				}
				else
				{
					dynamic_cast<CSword*>(target[i]->getWeapon())->setDurability(dynamic_cast<CSword*>(target[i]->getWeapon())->getDurability() + randDurability(3, 15));
					if (dynamic_cast<CSword*>(target[i]->getWeapon())->getDurability() > dynamic_cast<CSword*>(target[i]->getWeapon())->getDurabilityMax())
					{
						dynamic_cast<CSword*>(target[i]->getWeapon())->setDurability(dynamic_cast<CSword*>(target[i]->getWeapon())->getDurabilityMax());
					}
				}
			}

		}
	}
}

int CWarrior::randDurability(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}
