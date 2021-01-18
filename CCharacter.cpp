#include "CCharacter.h"
using namespace std;

//pour comter le nombre de personnage presennt sur le terrain
int CCharacter::m_characterNumber = 0;

//constructeur par defaut 
CCharacter::CCharacter()
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
	m_lifeMax = 0.0f;
	m_speedInit = 0.0f;
	m_choiceWeapon = None;
}

//constructeur parametrique
CCharacter::CCharacter(string name, float life, float dodge, float speed, float attack, float defence, float agility, float intelligence)
{
	m_weapon = NULL;
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
	m_lifeMax = life;
	m_speedInit = m_speed;
	m_choiceWeapon = None;
}

//destructeur
CCharacter::~CCharacter()
{
	m_characterNumber--;
	if (m_weapon != NULL)
		delete m_weapon;
}

//methode pour calculer le coefficient lorsqu'un personnage attaque (avec ou sans arme)
float CCharacter::randCoef(float min, float max)
{
	min *= 100.0f;
	max *= 100.0f;

	return ((rand() % ((int)max - (int)min + 1)) + min) / 100.0f;
}

//methode pour calculer la chance d'esquive
float CCharacter::dodgeChance() 
{
	return ((rand() % 100)) / 100.0f;
}

//methode pour que la cible recoive les degat
void CCharacter::beHurt(float damages)
{
	m_life -= damages;
	if (m_life < 0.0f)
		m_life = 0.0f;
}

//methode polymorphique pour calculer les degas du personnage qui attaque a mains nues
float CCharacter::damageCalculation(CCharacter* target)
{
	return ((16.0f * m_attack * randCoef(MIN_COEF_CHARACTER, MAX_COEF_CHARACTER)) / target->getDefence());;
}

//methode polymorphique pour que le personnage esquive
void CCharacter::dodge(float damages)
{
	if (this->dodgeChance() > this->getDodge())
		this->beHurt(damages);
	else
		cout << "Miss...\n" << endl;
}

//fonction qui appelle les methodes polymorphiques gerant lattaque d'un personnage avec une arme sur un autre
void attackSomeone(CCharacter* assailant, CCharacter* target)
{
	float damages = 0.0f;
	
	cout << assailant->getName() << " attaque " << target->getName() << "!!!\n";

	if (assailant->getWeapon() == NULL)
		damages = assailant->CCharacter::damageCalculation(target);
	else
	{
		if (assailant->getChoiceWeapon() == Daguer)
		{
			if (dynamic_cast<CDagger*>(assailant->getWeapon())->getStateDelight() == true)
			{
				cout << "L'arme de " << assailant->getName() << " brille et attaque avec plus de force.\n";
				assailant->getWeapon()->setAttack(assailant->getWeapon()->getAttack() + (assailant->getWeapon()->getAttack() / 3.0f));
				dynamic_cast<CDagger*>(assailant->getWeapon())->setStateDelight(false);
			}
			dynamic_cast<CDagger*>(assailant->getWeapon())->updateDurability();
		}
		if (assailant->getChoiceWeapon() == Sword)
		{
			if (dynamic_cast<CSword*>(assailant->getWeapon())->getStateDelight() == true)
			{
				cout << "L'arme de " << assailant->getName() << " brille et attaque avec plus de force.\n";
				assailant->getWeapon()->setAttack(assailant->getWeapon()->getAttack() + (assailant->getWeapon()->getAttack() / 3.0f));
				dynamic_cast<CSword*>(assailant->getWeapon())->setStateDelight(false);
			}
			dynamic_cast<CSword*>(assailant->getWeapon())->updateDurability();
		}
		damages = assailant->damageCalculation(target);
	} 

	target->dodge(damages);
}

//fonction qui appelle les methodes polymorphiques gerant l'attaque d'un personnage sans arme sur un autre
void attackSomeoneWithoutWeapon(CCharacter* assailant, CCharacter* target)
{
	cout << assailant->getName() << " attaque " << target->getName() << " a mains nues!!!\n";
	float damages = assailant->CCharacter::damageCalculation(target);
	target->dodge(damages);
}

//fonction qui appplle les methodes polymorphiques pour verifer quue le personnage
//a une arme correcte puis modifier les stats de ce dernier en fontion 
void initCharacter(CCharacter* target)
{
	target->checkWeapon();
	target->updateCharacter();
}

//methode polymorphique pour choisir l'action du personnage
int CCharacter::choiceMove()
{
	cout << "Que voullez vous faire?\n";
	cout << "en fait vous n'avez pas le choix: vous attaquez a mains nues\n";
	return AttackWithoutWeapon;
}


//fonction qui appelle la methode polymorphique pour gerer l'action du personnage
int action(CCharacter* charcter)
{
	return charcter->choiceMove();
}

//methode polymorphique pour mettre a jour les stats du personnage
void CCharacter::updateStates()
{
	if (m_stateProvocation > 0)
		m_stateProvocation--;

	if (m_statePoison == true)
		m_life /= 12.0f;
}

//methode pour recuper l'amer des personnage dans les fichiers
CWeapon* CCharacter::readFileWeappon(std::string path)
{
	string weapon = "";
	string name = "";
	float life = 0.0f;
	float manaUsed = 0.0f;
	float intelligence = 0.0f;
	float critChance = 0.0f;
	float damage = 0.0f;
	float attack = 0.0f;
	float agility = 0.0f;
	int arrowNumber = 0;
	int durability = 0;
	float defence = 0.0f;

	ifstream file(path, ios::in);
	if (file.is_open())
	{
		file >> weapon;
		if (weapon == "Baton")
		{
			m_choiceWeapon = Staff;
			file >> name >> life >> manaUsed >> intelligence >> critChance >> damage >> attack;
			return (new CStaff(manaUsed, critChance, damage, name, life, attack, intelligence));
		}
		else if (weapon == "Epee")
		{
			m_choiceWeapon = Sword;
			file >> name >> critChance >> attack >> durability >> damage >> life;
			return (new CSword(critChance, damage, durability, name, attack, life));
		}
		else if (weapon == "Arc")
		{
			m_choiceWeapon = Bow;
			file >> name >> critChance >> attack >> damage >> arrowNumber >> life;
			return (new CBow(arrowNumber, critChance, damage, name, attack, life));
		}
		else if (weapon == "Dague")
		{
			m_choiceWeapon = Daguer;
			file >> name >> damage >> life >> defence >> durability >> critChance >> attack >> agility;
			return (new CDagger(critChance, damage, durability, name, life, defence, attack, agility));
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

//mthode pour faire la rotation des fichier lus
string CCharacter::selectFile()
{
	if (m_characterNumber == 0)
		return "weaponTeam1Character1.txt";

	if (m_characterNumber == 1)
		return "weaponTeam1Character2.txt";

	if (m_characterNumber == 2)
		return "weaponTeam1Character3.txt";

	if (m_characterNumber == 3)
		return "weaponTeam2Character1.txt";

	if (m_characterNumber == 4)
		return "weaponTeam2Character2.txt";

	if (m_characterNumber == 5)
		return "weaponTeam2Character3.txt";
}

//methodes pour determiner si un personnage aura une arme
CWeapon* CCharacter::initWeapon()
{
	CWeapon* weapon = NULL;
	string path = selectFile();
	int choice = 0;

	cout << "Ce perso doit-il avoir une arme ?\n0. non\n1. oui\n";
	cin >> choice;

	if (choice == 1)
		weapon = readFileWeappon(path);

	m_characterNumber++;

	return weapon;
}

//methode polymorphique pour verifier l'arme d'un personnage
void CCharacter::checkWeapon()
{
	cout << "Nothing...\n";
}

//methode polymorphique pour mettre a jour les stats d'un personnage
void CCharacter::updateCharacter()
{
	m_attack += m_weapon->getAttack();
	m_life += m_weapon->getLife();
}

//fonction qui appelle la methode polymorphique de gestion de stat
void updateCharachers(CCharacter* target)
{
	target->updateStates();	
}

//methode polymorphique pour presenter un personnage
void CCharacter::dispCharacter()
{
	cout << "Nom:\t\t\t" << m_name << "\n";
	cout << "Attaque:\t\t" << m_attack << "\n";
	cout << "Vie:\t\t\t" << m_life << "\n";
	cout << "Agilite:\t\t" << m_agility << "\n";
	cout << "Esquive:\t\t" << m_dodge << "\n";
	cout << "Arme:\t\t\t" << m_weapon->getName() << "\n";
	cout << "Defence:\t\t" << m_defence << "\n";
	cout << "Inteligence:\t\t" << m_intelligence << "\n";
	cout << "Vitesse:\t\t" << m_speed << "\n";
	cout << "Poison:\t\t\t" << m_statePoison << "\n";
	cout << "Provocation:\t\t" << m_stateProvocation << "\n";
	cout << "\n";
}

//fonction qui appelle la methode polymorphique qui presente un personnage
void presentCharacter(vector<CCharacter*> target)
{
	for (int i = 0; i < target.size(); i++)
	{
		cout << "Perso " << (i + 1 )<< "\n";
		target[i]->dispCharacter();
	}
}

//**************************assesseurs / muttateurs**************************
float CCharacter::getDefence()
{
	return m_defence;
}

float CCharacter::getDodge()
{
	return m_dodge;
}

void CCharacter::setDodge(float dodge)
{
	m_dodge = m_dodge;
}

void CCharacter::setStateProvocation(int time)
{
	m_stateProvocation = time;
}

void CCharacter::setStatePoison(bool state)
{
	m_statePoison = state;
}

float CCharacter::getLife()
{
	return m_life;
}

float CCharacter::getLifeMax()
{
	return m_life;
}

void CCharacter::setLife(float life)
{
	m_life = life;
}

std::string CCharacter::getName()
{
	return m_name;
}

void CCharacter::setName(std::string name)
{
	m_name = name;
}

void CCharacter::setSpeed(float speed)
{
	m_speed = speed;
}

CWeapon* CCharacter::getWeapon()
{
	return m_weapon;
}

int CCharacter::getChoiceWeapon()
{
	return m_choiceWeapon;
}

float CCharacter::getSpeed()
{
	return m_speed;
}

float CCharacter::getSpeedInit()
{
	return m_speedInit;
}

bool CCharacter::getStatePoison()
{
	return m_statePoison;
}



