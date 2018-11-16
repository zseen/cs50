#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int coinsCounter = 0;
    double money = -1;
	int coinValues[4] = { 25, 10, 5, 1 };

	while (money < 0)
	{
		money = get_double("How much should the change be?: ");
	}

	money = money * 100;

	while (money != 0)
		for (int i = 0; i < 4; i++)
		{
		    coinsCounter += money / coinValues[i];
			money = (int)money % coinValues[i];
		}

	printf("%i\n", coinsCounter);
}