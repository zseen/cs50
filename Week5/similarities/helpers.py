from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    linesInA = a.splitlines()
    linesInB = b.splitlines()

    commonLinesList = []
    for line in linesInA:
        if line in linesInB and line not in commonLinesList:
            commonLinesList.append(line)

    return commonLinesList


def sentences(a, b):
    """Return sentences in both a and b"""

    sentencesInA = sent_tokenize(a, language='english')
    sentencesInB = sent_tokenize(b, language='english')

    commonSentencesList = []
    for sentence in sentencesInA:
        if sentence in sentencesInB and sentence not in commonSentencesList:
            commonSentencesList.append(sentence)

    return commonSentencesList


def getSubstringsInString(string, size):
    substringsList = []
    for char in range(0, len(string) - size + 1):
        substringsList.append(string[char: char + size])

    return substringsList


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    substringsOfFirstString = getSubstringsInString(a, n)
    substringsOfSecondString = getSubstringsInString(b, n)

    commonSubstringsList = []
    for substring in substringsOfFirstString:
        if substring in substringsOfSecondString and substring not in commonSubstringsList:
            commonSubstringsList.append(substring)

    return commonSubstringsList



