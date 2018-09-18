height = -1
while height < 0 or height > 23:
    try:
        height = int(input("Height: "))
    except:
        pass

for i in range(0, height):
    print((height - i - 1) * " " + (i + 1) * "#" + "#")