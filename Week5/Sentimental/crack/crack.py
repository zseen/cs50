import crypt
import sys


def generateSameLetterString(size, letter):
    sameLetterString = []
    for i in range(0, size):
        sameLetterString.append(letter)

    return ''.join(sameLetterString)


def generateSameLetterStringWith_A(size):
    onlyLetter_A = generateSameLetterString(size, 'A')
    return onlyLetter_A


def generateSameLetterStringWith_z(size):
    onlyLetter_z = generateSameLetterString(size, 'z')
    return onlyLetter_z


def getLexicographicalNextString(word):
    word = list(word)
    for i in range(len(word) - 1, -1, -1):
        if word[i] == 'Z':
            word[i] = 'a'
            break
        elif word[i] == 'z':
            word[i] = 'A'
        else:
            charAtPositionI = ord(word[i])
            charAtPositionI += 1
            word[i] = str(chr(charAtPositionI))

    return ''.join(word)


def crackHashedWord(targetHash, salt):
    for wordLength in range(1, 6):
        currentWord = generateSameLetterStringWith_A(wordLength)
        finalWord = generateSameLetterStringWith_z(wordLength)

        while True:
            if currentWord == finalWord:
                break

            hashedWord = crypt.crypt(currentWord, salt)
            if hashedWord == targetHash:
                return currentWord

            nextCurrentWord = getLexicographicalNextString(currentWord)
            currentWord = nextCurrentWord


def main():
    if len(sys.argv) != 2:
        print("Usage: python crack.py hashedPassword")
        exit(1)

    targetHash = sys.argv[1]
    salt = targetHash[0] + targetHash[1]
    
    password = crackHashedWord(targetHash, salt) 
    print(password)

if __name__ == '__main__':
    main()
