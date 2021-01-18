#include "CMage.h"
using namespace std;

//constructeur par defaut 
CMage::CMage()
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
	m_mana = 0.0f;
	m_lifeMax = 0.0f;
	m_speedInit = 0.0f;
	m_stateProvocation = 0;
	m_statePoison = false;
	m_cooldownHeal = 0;
	m_cooldownDelight = 0;
}

//condtructeur parametrique
CMage::CMage(std::string name, float life, float dodge, float speed, float attack, float defence, float agility, float intelligence)
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
	m_mana = intelligence * 10.0f;
	m_lifeMax = life;
	m_speedInit = speed;
	m_stateProvocation = 0;
	m_statePoison = false;
	m_cooldownHeal = 0;
	m_cooldownDelight = 0;
}

//destructeur
CMage::~CMage()
{
	m_characterNumber--;
	if(m_weapon != NULL)
		delete m_weapon;
}

//methode polymorphique pour calculer les degat d'un mage
float CMage::damageCalculation(CCharacter* target)
{
	return ((5.0f * (m_intelligence + m_weapon->getDamage()) * randCoef(MIN_COEF_MAGE, MAX_COEF_MAGE)) / target->getDefence());
}

//methode polymorphique d'un mage pour esquiver
void CMage::dodge(float damages)
{
	if (this->dodgeChance() > this->getDodge())
	{
		this->beHurt(damages);
		cout << m_name << " prend " << damages << " degats\n" << endl;
	}
	else
		cout << "Miss...\n";
}

//methode polymorphique pour presenter un mage
void CMage::dispCharacter()
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
	cout << "Mana:\t\t\t" << m_mana << "\n";
	cout << "CD Enchantement:\t" << m_cooldownDelight << "\n";
	cout << "CD Soin:\t\t" << m_cooldownHeal << "\n";
	cout << "Poison:\t\t\t" << m_statePoison << "\n";
	cout << "Provocation:\t\t" << m_stateProvocation << "\n";
	if (m_weapon != NULL)
	{
		if (m_choiceWeapon == Sword)
		{
			cout << "EtatArme:\t\t" << dynamic_cast<CSword*>(m_weapon)->getDurability() << "\n";
		}
	}
	cout << "\n";
}

//methode polymorphique pour verifier s l'arme tenue par le mage est correcte
void CMage::checkWeapon()
{
	if (m_choiceWeapon == Bow || m_choiceWeapon == Daguer)
	{
		cout << "L'arme de " << m_name << " n'est pas correcte. On lui la retire.\n";
		delete m_weapon;
		m_weapon = NULL;
		m_choiceWeapon = None;
	}
}

//methode polymorphique pour modifier les stat du mage en fonction de son arme tenue
void CMage::updateCharacter()
{
	if (m_weapon != NULL)
	{
		if (m_choiceWeapon == Staff)
		{
			m_attack += m_weapon->getAttack();
			m_life += m_weapon->getLife();
			m_intelligence += dynamic_cast<CStaff*>(m_weapon)->getIntelligence();
		}
		if (m_choiceWeapon == Sword)
		{
			m_attack += m_weapon->getAttack();
			m_life += m_weapon->getLife();
		}
	}
}

//methode polymorphique pour choisir l'action d'un mage
int CMage::choiceMove()
{
	if (m_stateProvocation > 0)
	{
		cout << "Sous la provocation " << m_name << " attaque avec son arme.\n";
		return AttackWithWeapon;
	}

	int choice = No;
	cout << "Que voulez vous faire?\n";
	cout << "1. Attaquer sans arme\n2. Attaquer avec une arme\n3. Regenerer votre mana\n4. Soigner un coequipier.\n5. Enchanter une arme de votre equipe\n" << endl;
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
		return RegenerateMana;
		break;
	case 4:
		return HealSomeone;
		break;
	case 5:
		return DelightWeapon;
		break;
	default:
		cout << "Vous avez fait le mauvait choix. Votre perso attaque a mains nues\n";
		return AttackWithoutWeapon;
		break;
	}
}

//methode pour reener la mana du mage
void CMage::regenerateMana()
{
	if (m_mana < MANA_MAX)
	{
		cout << m_name << " regenere sa mana.\n";
		m_mana += randMana(2, 7);
		if (m_mana > MANA_MAX)
			m_mana = MANA_MAX;
	}
	else
		cout << "\nMais vous avez toute votre mana\n" << endl;
}

//methode pour soigner un membre de son equipe
void CMage::heal(CCharacter* target)
{
	if (m_choiceWeapon == Staff)
	{
		if (target->getLife() < target->getLifeMax())
		{
			cout << m_name << " regenere la vie de " << target->getName() << ".\n";
			target->setLife(target->getLifeMax() + randLfe(10, 20));
			if (target->getLife() > target->getLifeMax())
				target->setLife(target->getLifeMax());

			m_mana -= 5;
			if (m_mana < 0)
				m_mana = 0;

			m_cooldownHeal = 4;
		}
		else
			cout << "\nMais vous avez toute votre vie\n";
	}
	else
	{
		cout << "\nNon!!! Il faut un baton!\n";
		cout << "A defaut vous choisisszez de regenerer votre mana...\n";
		this->regenerateMana();
	}
}

//methode polymorphique pour mettre ajour les stats du mage a chaque tour 
void CMage::updateStates()
{
	if (m_stateProvocation > 0)
		m_stateProvocation--;

	if (m_cooldownDelight > 0)
		m_cooldownDelight--;

	if (m_cooldownHeal > 0)
		m_cooldownHeal--;

	if (m_choiceWeapon == Sword)
	{
		if (dynamic_cast<CSword*>(m_weapon)->getDurability() < 0)
			dynamic_cast<CSword*>(m_weapon)->setState(false);
	}
}

//**************************methode qui retourne une valeur alleatoire**************************
float CMage::randMana(int min, int max)
{
	return ((rand() % (max - min + 1)) + min) / 1.0f;
}

float CMage::randLfe(int min, int max)
{
	return ((rand() % (max - min + 1)) + min) / 1.0f;
}

//methode pour enchanter l'arme d'un membre de son equipe
void CMage::delight(CCharacter* target)
{
	if (target->getWeapon() != NULL)
	{
		if (target->getChoiceWeapon() == Daguer || target->getChoiceWeapon() == Sword)
		{
			cout << m_name << " enchante l'arme de " << target->getName() << ".\n";
			m_mana -= 7.0f;
			m_cooldownDelight = 3;
		}
		else
			cout << target->getName() <<" n'a pas d'arme de melee.\n";
		if (target->getChoiceWeapon() == Sword)
		{
			dynamic_cast<CSword*>(target->getWeapon())->setStateDelight(true);
			
		}
		if (target->getChoiceWeapon() == Daguer)
		{
			dynamic_cast<CDagger*>(target->getWeapon())->setStateDelight(true);
		}
		
	}
	else
		cout << target->getName() << " n'a pas d'arme.\n";
}
