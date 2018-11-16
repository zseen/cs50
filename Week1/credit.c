#include <stdio.h>
#include <cs50.h>


int checkLength(long long cardNumber)
{
	int length = 0;

	while (cardNumber != 0)
	{
		++length;
		cardNumber /= 10;
	}
	return length;
}

int getStartingCharacters(long long cardNumber)
{
	int firstTwoChars = 0;
	while (cardNumber > 99)
	{
		firstTwoChars = cardNumber % 10;
		cardNumber /= 10;
	}
	return cardNumber;
}

int multiplyDigitsFromBehind(long long cardNumber)
{
	int allDigitsModifiedSum = 0;

	while (cardNumber != 0)
	{
		allDigitsModifiedSum += cardNumber % 10;
		cardNumber /= 10;

		if (cardNumber % 10 > 4)
		{
			allDigitsModifiedSum += cardNumber % 10 * 2 % 10 + 1;
		}

		else
		{
			allDigitsModifiedSum += (cardNumber % 10) * 2;
		}

		cardNumber /= 10;
	}
	return allDigitsModifiedSum;
}

string determineCardType(long long cardNumber)
{
	int firstTwoChars = getStartingCharacters((long long)cardNumber);

	int cardNumberLength = checkLength((long long)cardNumber);

	int allDigitsSum = multiplyDigitsFromBehind((long long)cardNumber);

	if (allDigitsSum % 10 == 0)
	{

		if (cardNumberLength == 15 && (firstTwoChars == 37 || firstTwoChars == 34))
		{
			return "AMEX\n";
		}

		else if ((firstTwoChars >= 40 && firstTwoChars <= 49) && (cardNumberLength == 13 || cardNumberLength == 16))
		{
			return "VISA\n";
		}
		else if ((firstTwoChars >= 51 && firstTwoChars <= 55) && cardNumberLength == 16)
		{
			return "MASTERCARD\n";
		}
		else
		{
			return "INVALID\n";
		}
	}
	else
	{
		return "INVALID\n";
	}
}


int main()
{
	long long cardNumber = -1;

	while ((long long)cardNumber < 0)
	{
		cardNumber = get_long_long("Card number please: ");
	}

	string result = determineCardType((long long)cardNumber);
	printf("%s", result);
}
