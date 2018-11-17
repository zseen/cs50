#include <stdio.h>
#include <cs50.h>

int getLength(long long cardNumber)
{
    int length = 0;

    while (cardNumber != 0)
    {
        ++length;
        cardNumber /= 10;
    }
    return length;
}

long long getStartingCharacters(long long cardNumber)
{
    int firstTwoChars = 0;
    while (cardNumber > 99)
    {
        firstTwoChars = cardNumber % 10;
        cardNumber /= 10;
    }
    return cardNumber;
}

int getDigitsModifiedSum(long long cardNumber)
{
    int allDigitsModifiedSum = 0;

    while (cardNumber != 0)
    {
        int cardNumberLastDigit = cardNumber % 10;

        allDigitsModifiedSum += cardNumberLastDigit;
        cardNumber /= 10;

        cardNumberLastDigit = cardNumber % 10;
        int cardNumberLastDigitTimesTwo = cardNumberLastDigit * 2;

        if (cardNumberLastDigitTimesTwo >= 10)
        {
            allDigitsModifiedSum += (cardNumberLastDigitTimesTwo % 10) + 1;
        }
        else
        {
            allDigitsModifiedSum += cardNumberLastDigitTimesTwo;
        }

        cardNumber /= 10;
    }
    return allDigitsModifiedSum;
}

char* determineCardType(long long cardNumber)
{
    long long firstTwoChars = getStartingCharacters(cardNumber);
    int cardNumberLength = getLength(cardNumber);
    int allDigitsSum = getDigitsModifiedSum(cardNumber);

    if (allDigitsSum % 10 == 0)
    {
        if (cardNumberLength == 15 && (firstTwoChars == 37 || firstTwoChars == 34))
        {
            return "AMEX";
        }
        else if ((firstTwoChars >= 40 && firstTwoChars <= 49) && (cardNumberLength == 13 || cardNumberLength == 16))
        {
            return "VISA";
        }
        else if ((firstTwoChars >= 51 && firstTwoChars <= 55) && cardNumberLength == 16)
        {
            return "MASTERCARD";
        }
        else
        {
            return "INVALID";
        }
    }
    else
    {
        return "INVALID";
    }
}

int main()
{
    long long cardNumber = -1;

    while (cardNumber < 0)
    {
        cardNumber = get_long_long("Card number please: ");
    }

    char* result = determineCardType(cardNumber);
    printf("%s\n", result);
}
