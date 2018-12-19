import sys


ALPHABET_LENGTH = 26
ASCII_UPPERCASE_A = 65
ASCII_LOWERCASE_A = 97


def encryptWord(word, key):
    encryptedWord = []

    for char in word:
        if not char.isalpha():
            encryptedWord.append(char)
        elif char.isupper():
            encryptedLetter = getEncryptedLetter(ASCII_UPPERCASE_A, char, key)
            encryptedWord.append(encryptedLetter)
        else:
            encryptedLetter = getEncryptedLetter(ASCII_LOWERCASE_A, char, key)
            encryptedWord.append(encryptedLetter)

    return ''.join(encryptedWord)


def getEncryptedLetter(asciiCaseA, char, key):
    letter = ((ord(char) + key) - asciiCaseA) % ALPHABET_LENGTH + asciiCaseA
    return str(chr(letter))


def main():
    if len(sys.argv) != 2:
        exit(1)

    key = sys.argv[1]
    plaintext = input("Give me a word to cipher!: ")
    ciphertext = encryptWord(plaintext, int(key))
    print("plaintext: ", plaintext)
    print("ciphertext: ", ciphertext)


if __name__ == '__main__':
    main()
