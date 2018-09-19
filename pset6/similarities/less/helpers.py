from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    l1 = set(a.split("\n"))
    l2 = set(b.split("\n"))

    common_lines = []

    for line in l1:
        if line in l2:
            common_lines.append(line)

    return common_lines


def sentences(a, b):
    """Return sentences in both a and b"""

    l1 = set(sent_tokenize(a))
    l2 = set(sent_tokenize(b))

    common_sentences = []

    for sentence in l1:
        if sentence in l2:
            common_sentences.append(sentence)

    return common_sentences


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    l1 = []
    for i in range(len(a) - n + 1):
        if a[i:i + n] not in l1:
            l1.append(a[i:i + n])

    l2 = []
    for i in range(len(b) - n + 1):
        if b[i:i + n] not in l2:
            l2.append(b[i:i + n])

    common_substrings = []

    for substring in l1:
        if substring in l2:
            common_substrings.append(substring)

    return common_substrings
