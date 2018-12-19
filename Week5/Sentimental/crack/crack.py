import crypt
import sys


def getLexicographicalNextString(word):
    word = list(word)
    for currentPosition in range(len(word) - 1, -1, -1):
        if word[currentPosition] == 'Z':
            word[currentPosition] = 'a'
            break
        elif word[currentPosition] == 'z':
            word[currentPosition] = 'A'
        else:
            charAtCurrentPosition = ord(word[currentPosition])
            charAtCurrentPosition += 1
            word[currentPosition] = str(chr(charAtCurrentPosition))

    return ''.join(word)


def crackHashedWord(targetHash, salt):
    for wordLength in range(1, 6):
        currentWord = wordLength * 'A'
        finalWord = wordLength * 'z'

        while True:
            if currentWord == finalWord:
                break

            hashedWord = crypt.crypt(currentWord, salt)
            if hashedWord == targetHash:
                return currentWord

            nextCurrentWord = getLexicographicalNextString(currentWord)
            currentWord = nextCurrentWord


def crackPassword(targetHash):
    salt = targetHash[0] + targetHash[1]
    return crackHashedWord(targetHash, salt)


def main():
    if len(sys.argv) != 2:
        print("Usage: python crack.py hashedPassword")
        exit(1)

    targetHash = sys.argv[1]

    password = crackPassword(targetHash)
    print(password)

if __name__ == '__main__':
    main()
