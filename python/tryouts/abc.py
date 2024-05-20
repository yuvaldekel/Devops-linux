def main():
    print(alphabet())

def alphabet():
        
    abc = []
    a = 'a'
    while a >= 'a' and a <= 'z':
        abc.append(a)
        a =chr(ord(a) +1)

    a ="A"
    while a >= 'A' and a <= 'Z':
        abc.append(a)
        a =chr(ord(a) +1)
        
    abc = ''.join(abc)
    return abc

main()