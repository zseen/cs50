import sys


ALPHABET_LENGTH = 26
ASCII_UPPERCASE_A = 65
ASCII_LOWERCASE_A = 97


def encryptWord(plainWord, key):
    encryptedWord = []
    keyLength = len(key)
    keyIndex = 0

    for i in range(len(plainWord)):
        if plainWord[i].isalpha():
            keycharInt = ord((key[keyIndex % keyLength].upper()))
            keychar = (keycharInt - ASCII_UPPERCASE_A) % 26

            if plainWord[i].isupper():
                encryptedLetter = getEncryptedLetter(ASCII_UPPERCASE_A, keychar, plainWord[i])
                encryptedWord.append(encryptedLetter)
            else:
                encryptedLetter = getEncryptedLetter(ASCII_LOWERCASE_A, keychar, plainWord[i])
                encryptedWord.append(encryptedLetter)
            keyIndex += 1
        else:
            encryptedWord.append(plainWord[i])

    return ''.join(encryptedWord)


def getEncryptedLetter(asciiCaseA, keychar, plainWordChar):
    letter = str(chr(((ord(plainWordChar) + keychar) - asciiCaseA) % ALPHABET_LENGTH + asciiCaseA))
    return letter


def main():
    if len(sys.argv) != 2:
        print("Give me one key to encript with! ")
        exit(1)

    key = sys.argv[1]
    if not key.isalpha():
        print("Your key should only consist of letters!")
        exit(1)

    plaintext = input("Give me a word to cipher!: ")
    encryptedWord = encryptWord(plaintext, key)

    print("plaintext: ", plaintext)
    print("ciphertext: ", encryptedWord)

if __name__ == '__main__':
    main()
