def getCountWithGreedy(number):
    valueTypes = [25, 10, 5, 1]
    operationCounter = 0

    while number:
        for value in valueTypes:
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
    money = (input("How much should the change be?: "))
    while (not isNumber(money)) or float(money) < 0:
        money = input("How much should the change be?: ")

    coinsNeeded = getCountWithGreedy(int(float(money) * 100))
    print(coinsNeeded)

if __name__ == '__main__':
    main()
