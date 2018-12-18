def drawHalfPyramid(height):
    for i in range(1, height + 1):
        for spacesNum in range(0, height - i):
            print(" ", end='')
        for hashesNum in range(0, i):
            print("#", end='')
        print('', end='')

        print('  ', end='')
        for hashesNum in range(0, i):
            print("#", end='')
        print('')


def main():
    height = input("How tall should the pyramid be? 0 <= height <= 23: ")
    while (not height.isdigit()) or (23 < int(height) or 0 > int(height)):
        height = input("How tall should the pyramid be? 0 <= height <= 23: ")

    drawHalfPyramid(int(height))

if __name__ == '__main__':
    main()
