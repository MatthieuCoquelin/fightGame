#include "CArcher.h"
#include "CBow.h"
using namespace std;

//constructeur par defaut
CArcher::CArcher()
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
	m_statAim = false;
	m_hillNumber = 0;
	m_lifeMax = 0;
	m_speedInit = 0.0f;
}

//constructeur parametrique
CArcher::CArcher(std::string name, float life, float dodge, float speed, float attack, float defence, float agility, float intelligence)
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
	m_lifeMax = life;
	m_stateProvocation = 0;
	m_statePoison = false;
	m_statAim = false;
	m_hillNumber = 3;
	m_speedInit = speed;
}

//destructeur
CArcher::~CArcher()
{
	m_characterNumber--;
	if (m_weapon != NULL)
		delete m_weapon;
}

//methode pour viser avec l'arc
void CArcher::aim()
{
	if (m_statAim == false)
	{
		cout << m_name << " vise.\n";
		m_agility *= 1.33f;
		m_statAim = true;
	}
}

//methode pour pour empoisoiner l'equipe adverse
void CArcher::hillPoison (vector<CCharacter*> target)
{
	if (m_hillNumber > 0)
	{
		for (int i = 0; i < target.size(); i++)
		{
			if (target[i]->getStatePoison() == true)
			{
				cout << m_name << " soigne " << target[i]->getName() << " du poison.\n";
				target[i]->setStatePoison(false);
			}
			m_hillNumber--;
		}
	}
	else
		cout << "\nVous ne pouvez plus utiliser ce sort pour le combat\n";
}

//methode polymorphique pour calculer les degas relatif a l'acher
float CArcher::damageCalculation(CCharacter* target)
{
	return ((9.0f * (m_agility + m_weapon->getDamage()) * randCoef(MIN_COEF_ARCHER, MAX_COEF_ARCHER)) / target->getDefence());
}

//mthodev polymorphique d'esquive pour l'archer
void CArcher::dodge(float damages)
{
	if (this->dodgeChance() > m_dodge)
	{
		this->beHurt(damages);
		cout << m_name << " prend " << damages << " degats\n" << endl;
	}
	else
		cout << "Miss...\n" << endl;
}

//methode polymorphique pour presenter l'archer
void CArcher::dispCharacter()
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
	cout << "Soin(s) possible(s):\t" << m_hillNumber << "\n";
	cout << "Poison:\t\t\t" << m_statePoison << "\n";
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

//methode polymorphique pour mettre a jour les stats de l'archer
void CArcher::updateStates()
{
	if (m_stateProvocation > 0)
		m_stateProvocation--;

	if (m_choiceWeapon == Daguer)
	{
		if (dynamic_cast<CDagger*>(m_weapon)->getDurability() < 0)
			dynamic_cast<CDagger*>(m_weapon)->setState(false);
	}
}

//methode polymorphique pour verifier que l'arme tenue (designe dans les fichier de parametrage) est correcte
void CArcher::checkWeapon()
{
	if (m_choiceWeapon == Staff || m_choiceWeapon == Sword)
	{
		cout << "L'arme de " << m_name << " n'est pas correcte. On lui la retire.\n";
		delete m_weapon;
		m_weapon = NULL;
		m_choiceWeapon = None;
	}
}

//methode polymorphique pour faire varier les stat de l'acher en fonction de son arme
void CArcher::updateCharacter()
{
	if (m_weapon != NULL)
	{
		if (m_choiceWeapon == Bow)
		{
			m_attack += m_weapon->getAttack();
			m_life += m_weapon->getLife();
		}
		if (m_choiceWeapon == Daguer )
		{
			m_attack += m_weapon->getAttack();
			m_life += m_weapon->getLife();
			m_agility += dynamic_cast<CDagger*>(m_weapon)->getAgility();
			m_defence += dynamic_cast<CDagger*>(m_weapon)->getDefence();
		}
	}
}

//methode polymorphique polymorphique pour choisir l'action a realiser
int CArcher::choiceMove()
{
	if (m_stateProvocation > 0)
	{
		cout << "Sous la provocation " << m_name << " attaque avec son arme.\n";
		return AttackWithWeapon;
	}

	if (m_statAim == true)
	{
		cout << m_name << " tire.\n";
		return AttackWithWeapon;
	}
		
	int choice = No;
	cout << "Que voulez vous faire?\n";
	cout << "1. Attaquer sans arme\n2. Attaquer avec une arme\n3. Viser\n4. Guerir votre equipe du poison.\n" << endl;
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
		return Aim;
		break;
	case 4:
		return HealPoison;
		break;
	default:
		cout << "Vous avez fait le mauvait choix. Votre perso attaque a mains nues\n";
		return AttackWithoutWeapon;
		break;
	}
}


