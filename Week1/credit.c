#include <stdio.h>
#include <cs50.h>

int checkLength(cardNumber)
{
	int length = 0;

	while (cardNumber != 0)
	{
		length += 1;
		cardNumber /= 10;

	}
	return length;
}

int main()
{
	long long cardNumber = get_long_long("Card number please: ");



	int l = checkLength(cardNumber);
	printf("%d\n", l);

}


