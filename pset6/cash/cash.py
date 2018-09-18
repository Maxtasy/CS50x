import math

change = -0.01
while change < 0:
    try:
        change = round(float(input("Change owed: ")) * 100)
    except:
        pass

count = 0

while change >= 25:
    change -= 25
    count += 1

while change >= 10:
    change -= 10
    count += 1

while change >= 5:
    change -= 5
    count += 1

while change >= 1:
    change -= 1
    count += 1

print(count)