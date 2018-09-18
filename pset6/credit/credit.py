while True:
    try:
        number = int(input("Number: "))
        break
    except:
        pass

number = str(number)

card_brand = "INVALID"

# Build checksum

digits_to_stay = number[-1::-2]
digits_to_multiply = number[-2::-2]

nums = ""

for num in digits_to_multiply:
    nums += str((int(num) * 2))

sub_sum_1 = 0

for num in nums:
    sub_sum_1 += int(num)

sub_sum_2 = 0

for num in digits_to_stay:
    sub_sum_2 += int(num)

checksum = sub_sum_1 + sub_sum_2

if checksum % 10 == 0:
    if len(number) == 15 and number[:2] in ["34", "37"]:
        card_brand = "AMEX"
    elif len(number) == 16:
        if number[:2] in ["51", "52", "53", "54", "55"]:
            card_brand = "MASTERCARD"
        elif number[0] == "4":
            card_brand = "VISA"
    elif len(number) == 13 and number[0] == "4":
        card_brand = "VISA"

print(card_brand)