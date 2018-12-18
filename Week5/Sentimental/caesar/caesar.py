import sys


ALPHABET_LENGTH = 26

def encriptWord(word, key):
    encriptedWord = []
    ascii_A = 65
    ascii_a = 97

    for char in word:
        if not char.isalpha():
            encriptedWord.append(char)
        elif char == char.upper():
            appendLetterToEncriptedWord(ascii_A, char, encriptedWord, key)
        else:
            appendLetterToEncriptedWord(ascii_a, char, encriptedWord, key)

    return ''.join(encriptedWord)


def appendLetterToEncriptedWord(ascii_aOrA, char, encriptedWord, key):
    letter = ((ord(char) + key) - ascii_aOrA) % ALPHABET_LENGTH + ascii_aOrA
    encriptedWord.append(str(chr(letter)))


def main():
    if len(sys.argv) != 2:
        exit(1)

    key = sys.argv[1]
    while not key.isdigit():
        key = (input("Please give me a numerical key to encript with!: "))

    plaintext = input("Give me a word to cipher!: ")
    ciphertext = encriptWord(plaintext, int(key))
    print("plaintext: ", plaintext)
    print("ciphertext: ", ciphertext)


if __name__ == '__main__':
    main()
