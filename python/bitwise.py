class BitwiseNumber:
    def __init__(self, value):
        self.value = value

    def __and__(self, other):
        return type(self)(self.value & other.value)

    def __or__(self, other):
        return type(self)(self.value | other.value)

    def __xor__(self, other):
        return type(self)(self.value ^ other.value)

    def __invert__(self):
        return type(self)(~self.value)

    def __lshift__(self, places):
        return type(self)(self.value << places)

    def __rshift__(self, places):
        return type(self)(self.value >> places)

    def __str__(self):
        return f"{self.value}"

    def __repr__(self):
        return bin(self.value)
    
def main():
    num1 = BitwiseNumber(58)
    num2 = BitwiseNumber(7)

    print(f"{num1 =}, {num2 = }, {num1 and num2 = }")
    print(f"{num1 =}, {num2 = }, {num1 or num2 = }")
    print(f"{num1}, {~(num1)}")
    print(f"{repr(num1)}, {repr(~(num1))}")
    print(f"{num2}, {~(num2)}")
    print(f"{repr(num1)}, {num1 >> 2}")
    print(f"{repr(num1)}, {num1 << 1}")

if __name__ == "__main__":
    main()