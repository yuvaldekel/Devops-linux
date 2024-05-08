e = 2.718281828459045090795598298427648842334747314453125

def log(n, base = 10):

    decimal = False
    if n < 1:
        decimal = True
        n = int(1 / n)

    temp = 1
    y = 0 
    while n != temp:

        temp = temp * base
        y = y + 1
    
    if decimal:
        y = -1 * y

    return y 

def ln(n):
    return log(n, e)

def main():
    print(f'{e = :.4f}')
    print(log(0.333333333333,3))

if __name__ == "__main__":
    main() 
    