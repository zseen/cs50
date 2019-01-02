from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    linesInA = a.splitlines()
    linesInB = b.splitlines()

    return list(set(linesInA) & set(linesInB))


def sentences(a, b):
    """Return sentences in both a and b"""

    sentencesInA = sent_tokenize(a, language='english')
    sentencesInB = sent_tokenize(b, language='english')

    return list(set(sentencesInA) & set(sentencesInB))


def getSubstringsInString(string, size):
    substringsList = []
    for char in range(0, len(string) - size + 1):
        substringsList.append(string[char: char + size])

    return substringsList


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    substringsOfFirstString = getSubstringsInString(a, n)
    substringsOfSecondString = getSubstringsInString(b, n)

    return list(set(substringsOfFirstString) & set(substringsOfSecondString))

