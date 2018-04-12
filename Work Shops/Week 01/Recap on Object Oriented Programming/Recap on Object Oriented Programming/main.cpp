#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include "grenadier.h"

int main()
{
//	srand(time(NULL));

	grenadier James("James");
	grenadier George("George");

	bool keep_playing = true;
	do
	{
		//Show The Objects Heath
		James.printHealth();
		George.printHealth();

		std::cout << std::endl;
		//_getch();
		system("ping localhost>nul");

		James.attack(George);
		George.attack(James);

		std::cout << std::endl;
		//_getch();
		system("ping localhost>nul");

		if (James.isDead())
		{
			std::cout << James.getName() << " is dead" << std::endl;
			keep_playing = false;
		}

		if (George.isDead())
		{
			std::cout << George.getName() << " is dead" << std::endl;
			keep_playing = false;
		}

		system("ping localhost>nul");
	} while (keep_playing);

	system("PAUSE");
	return 0;
}