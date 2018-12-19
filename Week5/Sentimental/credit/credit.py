def getNumbersNotMultiplied(cardNum):
    digitsList = list(cardNum)
    notMultipliedValues = []
    startIndex = 0

    if len(digitsList) % 2 == 0:
        startIndex = 1

    for i in range(startIndex, len(cardNum), 2):
        notMultipliedValues.append(int(digitsList[i]))

    return notMultipliedValues


def getEveryOtherDigitFromBehindMultipliedByTwo(cardNum):
    digitsList = list(cardNum)
    multipliedValues = []

    for i in range(len(digitsList)-2, -1, -2):
        multipliedValues.append(int(digitsList[i]) * 2)

    return multipliedValues


def getDigitsSum(numsList):
    digitsSum = 0

    for item in numsList:
        digitsSum += sum(list(map(int, str(item))))

    return digitsSum


def isCardNumberValid(cardNum):
    notMultipliedDigits = getNumbersNotMultiplied(cardNum)
    multipliedDigitsList = getEveryOtherDigitFromBehindMultipliedByTwo(cardNum)
    multipliedDigitsListSum = getDigitsSum(multipliedDigitsList)
    isValidDigitsSum = ((multipliedDigitsListSum + sum(notMultipliedDigits)) % 10 == 0)
    return isValidDigitsSum


def getCardType(cardNum):
    isDigitsSumValid = isCardNumberValid(cardNum)

    if isDigitsSumValid:
        cardNumLength = len(cardNum)
        firstDigit = cardNum[0]
        secondDigit = cardNum[1]
        secondDigitAMEX = (secondDigit == "4" or secondDigit == "7")
        secondDigitMASTERCARD = ("1" <= secondDigit <= "5")
        cardNumLengthVISA = (cardNumLength == 13 or cardNumLength == 16)

        if isDigitsSumValid and cardNumLength == 15 and firstDigit == "3" and secondDigitAMEX:
                return "AMEX"

        elif isDigitsSumValid and cardNumLength == 16 and firstDigit == "5" and secondDigitMASTERCARD:
                return "MASTERCARD"

        elif isDigitsSumValid and cardNumLengthVISA and firstDigit == "4":
                return "VISA"

    return "INVALID"


def main():
    inputText = "Give me a credit card number!: "
    cardNumber = input(inputText)
    while (not cardNumber.isdigit()) or int(cardNumber) < 0:
        cardNumber = input(inputText)

    print(getCardType(cardNumber))

if __name__ == '__main__':
    main()
