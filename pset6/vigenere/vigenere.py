import sys
import string

if len(sys.argv) != 2:
    print("Usage: python vigenere.py <key>")
    exit(1)

key_word = sys.argv[1]

if not key_word.isalpha():
    print("Key needs to be alphabetical.")
    exit(1)

key_list = [string.ascii_lowercase.index(c.lower()) for c in key_word]

plain = input("plaintext: ")

cipher = ""

index = 0

for c in plain:
    if c.isupper():
        cipher += string.ascii_uppercase[(string.ascii_uppercase.index(c) + key_list[index]) % 26]
    elif c.islower():
        cipher += string.ascii_lowercase[(string.ascii_lowercase.index(c) + key_list[index]) % 26]
    else:
        cipher += c
    index = (index + 1) % len(key_list)

print("ciphertext: " + cipher)