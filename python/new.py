class A(int):
    __i = 0

    @staticmethod
    def __new__(cls, value):
        cls.add()
        instance = super(A, cls).__new__(cls, value)
        instance.num = cls.__i
        return instance

    def __init__(self, value) -> None:
        self.b = value

    @classmethod
    def add(cls):
        cls.__i += 1

    @classmethod
    def get_i(cls):
        return cls.__i

def main():
    a1 = A(4)
    a2 = A(5)

    print(f"i = {a1.get_i()}")    
    print(f"{a1.num = }")
    print(f"{a2.num = }")
    print(f"{a2 = }")

if __name__ == "__main__":
    main()