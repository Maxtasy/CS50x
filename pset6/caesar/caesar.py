import sys
import string

if len(sys.argv) != 2:
    print("Usage: python caesar.py <shift>")
    exit(1)

try:
    shift = int(sys.argv[1])
except:
    print("Shift needs to be a positive integer.")
    exit(1)

plain = input("plaintext: ")

cipher = ""

for c in plain:
    if c.isupper():
        cipher += string.ascii_uppercase[(string.ascii_uppercase.index(c) + shift) % 26]
    elif c.islower():
        cipher += string.ascii_lowercase[(string.ascii_lowercase.index(c) + shift) % 26]
    else:
        cipher += c

print("ciphertext: " + cipher)