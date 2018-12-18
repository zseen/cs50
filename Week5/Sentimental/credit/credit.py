def getEveryOtherDigitMultipliedAndListTheOthers(cardNum):
    digitsList = list(cardNum)
    multipliedValues = []
    notMultipliedValues = []
    if len(cardNum) % 2 != 0:
        notMultipliedValues = [int(digitsList[0])]

    for i in range(len(digitsList)-2, -1, -2):
        multipliedValues.append(int(digitsList[i]) * 2)
        notMultipliedValues.append(int(digitsList[i + 1]))

    return multipliedValues, notMultipliedValues


def getTotalSumOfTwoLists(multipliedNumsListSum, notModifiedNumsList):
    totalSum = multipliedNumsListSum + sum(notModifiedNumsList)
    return totalSum


def isNumsSumValid(number):
    if number % 10 == 0:
        return True
    return False


def validateCardType(isCardValid, cardNum):
    cardNumLength = len(cardNum)
    firstDigit = cardNum[0]
    secondDigit = cardNum[1]

    if isCardValid:
        if cardNumLength == 15 and firstDigit == "3" and (secondDigit == "4" or secondDigit == "7"):
            return "AMEX"

        elif cardNumLength == 16 and firstDigit == "5" and ("1" <= secondDigit <= "5"):
            return "MASTERCARD"

        elif (cardNumLength == 13 or cardNumLength == 16) and firstDigit == "4":
            return "VISA"

    return "INVALID"


def getDigitsSum(numsList):
    digitsSum = 0

    for item in numsList:
        if len(str(item)) > 1:
            item = sum(list(map(int, str(item))))
        digitsSum += int(item)

    return digitsSum


def main():
    cardNumber = input("Give me a credit card number!: ")
    while (not cardNumber.isdigit()) or int(cardNumber) < 0:
        cardNumber = input("Give me a credit card number!: ")

    modifiedListsTuple = getEveryOtherDigitMultipliedAndListTheOthers(cardNumber)
    multipliedDigitsListSum = getDigitsSum(modifiedListsTuple[0])
    total = getTotalSumOfTwoLists(multipliedDigitsListSum, modifiedListsTuple[1])
    isValid = isNumsSumValid(total)

    print(validateCardType(isValid, cardNumber))

if __name__ == '__main__':
    main()
