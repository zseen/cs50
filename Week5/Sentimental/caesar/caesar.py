ALPHABET_LENGTH = 26

def encriptWord(word, key):
    encriptedWord = []
    ascii_A = 65
    ascii_a = 97

    for char in word:
        if char == char.upper():
            appendLetterToEncriptedWord(ascii_A, char, encriptedWord, key)
        elif char == char.lower():
            appendLetterToEncriptedWord(ascii_a, char, encriptedWord, key)
        else:
            encriptedWord.append(char)

    return ''.join(encriptedWord)


def appendLetterToEncriptedWord(ascii_aOrA, char, encriptedWord, key):
    letter = ((ord(char) + key) - ascii_aOrA) % ALPHABET_LENGTH + ascii_aOrA
    encriptedWord.append(str(chr(letter)))


def main():
    key = (input("Please give me a numerical key to encript with!: "))
    while not key.isdigit():
        key = (input("Please give me a numerical key to encript with!: "))

    word = input("Give me a word to cipher!: ")
    encriptedWord = encriptWord(word, int(key))
    print(encriptedWord)


if __name__ == '__main__':
    main()
