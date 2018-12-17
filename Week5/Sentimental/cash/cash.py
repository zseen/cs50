def getCountWithGreedy(number):
    valueTypes = [25, 10, 5, 1]
    operationCounter = 0

    while number:
        for value in valueTypes:
            operationCounter += number // value
            number %= value

    return operationCounter


def main():
    money = float(input("How much should the change be?: "))
    while money < 0:
        money = float(input("How much should the change be?: "))

    coinsNeeded = getCountWithGreedy(int(money * 100))
    print(coinsNeeded)

if __name__ == '__main__':
    main()
