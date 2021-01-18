#include "CBow.h"
#include "CArcher.h"
#include "CMage.h"
#include "CRogue.h"
#include "CWarrior.h"
#include "CGame.h"

using namespace std;

int main(int argc, char** argv)
{
	srand(time(NULL));

	CGame myGame;
	myGame.loopGame();

	system("pause");
	return EXIT_SUCCESS;
}