#include "CRogue.h"
#include "CDagger.h"
using namespace std;

//constructeur par defaut par defaut 
CRogue::CRogue()
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
	m_stateProvocation = 0;
	m_statePoison = false;
	m_stateStealth = 0;
	m_lifeMax = 0.0f;
	m_speedInit = 0.0f;
	m_poisonChance = 0.0f;
	m_cooldownStealth = 0;
}

//constructeur parametrique 
CRogue::CRogue(std::string name, float life, float dodge, float speed, float attack, float defence, float agility, float intelligence, float poisonChance)
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
	m_stateProvocation = 0;
	m_statePoison = false;
	m_stateStealth = 0;
	m_lifeMax = life;
	m_speedInit = speed;
	m_poisonChance = poisonChance;
	m_cooldownStealth = 0;
}

//destructeur
CRogue::~CRogue()
{
	m_characterNumber--;
	if (m_weapon != NULL)
		delete m_weapon;
}

//methode polymorphique pour calculer le degats d'un voleur
float CRogue::damageCalculation(CCharacter* target)
{
	return ((7.0f * (m_agility + m_weapon->getDamage()) * randCoef(MIN_COEF_ROGUE, MAX_COEF_ROGUE)) / target->getDefence());
}

//methode polymorphique pour gerer l'esquive d'un voleur 
void CRogue::dodge(float damages)
{
	if (m_stateStealth == 0)
	{
		if (this->dodgeChance() > this->getDodge())
		{
			this->beHurt(damages);
			cout << m_name << " prend " << damages << " degats\n" << endl;
		}
		else
			cout << "Miss...\n" << endl;
	}
	if (m_stateStealth > 0)
		cout << "Le personnage invisible evite l'attaque\n" << endl;
}

//methode polymorphique pour presenter un voleur 
void CRogue::dispCharacter()
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
	cout << "Chance d'empoisonement:\t" << m_poisonChance << "\n";
	cout << "CD furtivite:\t\t" << m_cooldownStealth << "\n";
	cout << "Poison:\t\t\t" << m_statePoison << "\n";
	cout << "Furtivite:\t\t" << m_stateStealth << "\n";
	cout << "Provocation:\t\t" << m_stateProvocation << "\n";
	if (m_weapon != NULL)
	{
		if (m_choiceWeapon == Daguer)
		{
			cout << "EtatArme:\t\t" << dynamic_cast<CDagger*>(m_weapon)->getDurability() << "\n";
		}
	}
	cout << "\n";
}

//methode polymorphique pour verifier que l'arme tenue par le voleur est autorise
void CRogue::checkWeapon()
{
	
	if (m_choiceWeapon == Staff || m_choiceWeapon == Sword)
	{
		cout << "L'arme de " << m_name << " n'est pas correcte. On lui la retire.\n";
		delete m_weapon;
		m_weapon = NULL;
		m_choiceWeapon = None;
	}
}

//methode polymorphique pour modifier les stat d'un voleur en fonction de son arme 
void CRogue::updateCharacter()
{
	if (m_weapon != NULL)
	{
		if (m_choiceWeapon == Bow)
		{
			m_attack += m_weapon->getAttack();
			m_life += m_weapon->getLife();
		}
		if (m_choiceWeapon == Daguer)
		{
			m_attack += m_weapon->getAttack();
			m_life += m_weapon->getLife();
			m_agility += dynamic_cast<CDagger*>(m_weapon)->getAgility();
			m_defence += dynamic_cast<CDagger*>(m_weapon)->getDefence();
		}
	}
}

//methode polymorphique pour choisir l'action d'un voleur 
int CRogue::choiceMove()
{
	if (m_stateProvocation > 0)
	{
		cout << "Sous la provocation " << m_name << " attaque avec son arme.\n";
		return AttackWithWeapon;
	}

	int choice = No;
	cout << "Que voulez vous faire?\n";
	cout << "1. Attaquer sans arme\n2. Attaquer avec une arme\n3. Empoisoner un adversaire\n4. Devenir invisible.\n" << endl;
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
		return Poison;
		break;
	case 4:
		return Stealth;
		break;
	default:
		cout << "Vous avez fait le mauvait choix. Votre perso attaque a mains nues\n";
		return AttackWithoutWeapon;
		break;
	}
}

//methode pour empoisoner un adversaire 
void CRogue::poison(CCharacter* target)
{
	if (m_choiceWeapon == Daguer)
	{
		float poison = this->poisonChance();
		if (poison >= 0.0f && poison <= m_poisonChance)
		{
			cout << m_name << " empoisone " << target->getName() << " avec sa dague.\n";
			target->setStatePoison(true);
		}
		else
			cout << "L'empoisonnement echoue\n";
	}
	else
		cout << "\nIl faut une dague!!!\n";
}

//methode polymorphique pour mettre a jour les stats d'un voleur
void CRogue::updateStates()
{
	if (m_stateProvocation > 0)
		m_stateProvocation--;

	if (m_cooldownStealth > 0)
		m_cooldownStealth--;

	if (m_choiceWeapon == Daguer)
	{
		if (dynamic_cast<CDagger*>(m_weapon)->getDurability() < 0)
			dynamic_cast<CDagger*>(m_weapon)->setState(false);
	}
}

float CRogue::poisonChance()
{
	return ((rand() % 100)) / 100.00f;
}

//methodes pour devenir invisible
void CRogue::stealth()
{
	cout << m_name << " devient invisible.\n";
	m_stateStealth = randStealth(1, 2);
	m_cooldownStealth = 4;
}

int CRogue::randStealth(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}




