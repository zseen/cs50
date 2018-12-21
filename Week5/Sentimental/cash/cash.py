VALUE_TYPES = [25, 10, 5, 1]


def getCountWithGreedy(number):
    operationCounter = 0

    while number:
        for value in VALUE_TYPES:
            operationCounter += number // value
            number %= value

    return operationCounter


def isNumber(str):
    try:
        float(str)
        return True
    except ValueError:
        return False


def main():
    inputText = "How much should the change be?: "
    money = input(inputText)
    while (not isNumber(money)) or float(money) < 0:
        money = input(inputText)

    coinsNeeded = getCountWithGreedy(int(float(money) * 100))
    print(coinsNeeded)

if __name__ == '__main__':
    main()
