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
    height = "-1"
    while (not height.isdigit()) or (23 < int(height) or 0 > int(height)):
        height = input("How tall should the pyramid be? 0 <= height <= 23: ")

    drawHalfPyramid(int(height))

if __name__ == '__main__':
    main()
