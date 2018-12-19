def drawHalfPyramid(height):
    for i in range(1, height + 1):
        for spacesNum in range(0, height - i):
            print(" ", end='')
        printHashes(i)
        print('', end='')

        print('  ', end='')
        printHashes(i)
        print('')

def printHashes(numberOfHashes):
    for hashesNum in range(0, numberOfHashes):
        print("#", end='')


def main():
    inputText = "How tall should the pyramid be? 0 <= height <= 23: "
    height = input(inputText)
    while (not height.isdigit()) or (23 < int(height) or 0 > int(height)):
        height = input(inputText)

    drawHalfPyramid(int(height))

if __name__ == '__main__':
    main()
