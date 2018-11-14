#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int coinsCounter = 0;
    double money;

    do
    {
		money = get_double("How much should the change be?: ");
    }

    while(money < 0);
    {

        money = money * 100;
		//money = round(money);
		//printf("%f", money);

        coinsCounter += money / 25;
        money = (int)money % 25;

        coinsCounter += money / 10;
        money = (int)money % 10;

        coinsCounter += money / 5;
        money = (int)money % 5;

        coinsCounter += money / 1;

        printf("%i\n", coinsCounter);

		gets();
    }


}