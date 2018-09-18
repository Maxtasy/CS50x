height = -1
while height < 0 or height > 23:
    try:
        height = int(input("Height: "))
    except:
        pass

for i in range(1, height + 1):
    print((height - i) * " " + (i) * "#" + "  " + (i) * "#")