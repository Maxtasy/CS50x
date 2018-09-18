import sys
import string
import crypt

if len(sys.argv) != 2:
    print("Usage: python crack.py <hashed password>")
    exit(1)

hashed_pw = sys.argv[1]
salt = hashed_pw[0:2]

legal_letters = string.ascii_letters

length = 1

while length <= 5:
    if length == 1:
        for i in range(len(legal_letters)):
            guess = legal_letters[i]

            hashed_guess = crypt.crypt(guess, salt)

            if hashed_guess == hashed_pw:
                print(guess)
                exit(0)
        print("All possible passwords of length 1 exhausted.")
        length += 1

    elif length == 2:
        for i in range(len(legal_letters)):
            for j in range(len(legal_letters)):
                guess = legal_letters[i] + legal_letters[j]

                hashed_guess = crypt.crypt(guess, salt)

                if hashed_guess == hashed_pw:
                    print(guess)
                    exit(0)
        print("All possible passwords of length 2 exhausted.")
        length += 1

    elif length == 3:
        for i in range(len(legal_letters)):
            for j in range(len(legal_letters)):
                for k in range(len(legal_letters)):
                    guess = legal_letters[i] + legal_letters[j] + legal_letters[k]

                    hashed_guess = crypt.crypt(guess, salt)

                    if hashed_guess == hashed_pw:
                        print(guess)
                        exit(0)
        print("All possible passwords of length 3 exhausted.")
        length += 1

    elif length == 4:
        for i in range(len(legal_letters)):
            for j in range(len(legal_letters)):
                for k in range(len(legal_letters)):
                    for l in range(len(legal_letters)):
                        guess = legal_letters[i] + legal_letters[j] + legal_letters[k] + legal_letters[l]

                        hashed_guess = crypt.crypt(guess, salt)

                        if hashed_guess == hashed_pw:
                            print(guess)
                            exit(0)
        print("All possible passwords of length 4 exhausted.")
        length += 1

    elif length == 5:
        for i in range(len(legal_letters)):
            for j in range(len(legal_letters)):
                for k in range(len(legal_letters)):
                    for l in range(len(legal_letters)):
                        for m in range(len(legal_letters)):
                            guess = legal_letters[i] + legal_letters[j] + legal_letters[k] + legal_letters[l] + legal_letters[m]

                            hashed_guess = crypt.crypt(guess, salt)

                            if hashed_guess == hashed_pw:
                                print(guess)
                                exit(0)
        print("All possible passwords of length 5 exhausted.")
        length += 1

print("All possible passwords exhausted.")