import sys

total = 0
num = int(sys.argv[len(sys.argv) - 1])

for i in range(1, num + 1):
    total += len(str(i))


print(total)