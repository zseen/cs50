def drawHalfPyramid(height):
    for i in range(2, height + 2):
        for spacesNum in range(0, height - i + 1):
            print(" ", end='')
        for hashesNum in range(0, i):
            print("#", end='')
        print('')


def main():
    inputText = "How tall should the half-pyramid be? 0 <= height <= 23: "
    height = input(inputText)
    while (not height.isdigit()) or (23 < int(height) or 0 > int(height)):
        height = input(inputText)

    drawHalfPyramid(int(height))

if __name__ == '__main__':
    main()
