import sys


ALPHABET_LENGTH = 26


def encriptWord(plainWord, key):
    encriptedWord = []
    keyLength = len(key)
    ascii_A = 65
    ascii_a = 97
    keyIndex = 0

    for i in range(len(plainWord)):
        if plainWord[i].isalpha():
            keycharInt = ord((key[keyIndex % keyLength].upper()))
            keychar = (keycharInt - ascii_A) % 26

            if plainWord[i] == plainWord[i].upper():
                appendCharToEncriptedWord(ascii_A, encriptedWord, keychar, plainWord[i])
                keyIndex += 1
            else:
                appendCharToEncriptedWord(ascii_a, encriptedWord, keychar, plainWord[i])
                keyIndex += 1
        else:
            encriptedWord.append(plainWord[i])

    return ''.join(encriptedWord)


def appendCharToEncriptedWord(ascii_aOrA, encriptedWord, keychar, plainWordChar):
    letter = str(chr(((ord(plainWordChar) + keychar) - ascii_aOrA) % ALPHABET_LENGTH + ascii_aOrA))
    encriptedWord.append(letter)


def main():
    if len(sys.argv) != 2:
        print("Give me one key to encript with! ")
        exit(1)

    key = sys.argv[1]
    if not key.isalpha():
        print("Your key should only consist of letters!")
        exit(1)

    plaintext = input("Give me a word to cipher!: ")
    encriptedWord = encriptWord(plaintext, key)

    print("plaintext: ", plaintext)
    print("ciphertext: ", encriptedWord)

if __name__ == '__main__':
    main()
