class Storage(float):
    def __new__(cls, value: float, unit: str):
        instance = super().__new__(cls, value)
        return instance
    
    def __init__(self, value: float, unit: str) -> None:
        self.unit = unit

    def __add__(self, other) -> float:
        if not isinstance(other, type(self)):
            raise TypeError("unupported operand +: " 
                           f"'{type(self).__name__}' and '{type(other).__name__}'")

        if self.unit != other.unit:
            raise TypeError(f"incompatible usnits: '{self.unit}' and '{other.unit}'")

        return type(self)(super().__add__(other), self.unit)
    
    def __str__(self) -> str:
        return f"{super().__repr__()}{self.unit}"
    
    def __repr__(self) -> str:
        return f"Storage({super().__repr__()}, {self.unit})"
    
def main():
    s1 = Storage(5, "kg")
    s2 = Storage(10, "kg")

    try:
        s3 = s1 + s2
        
        print(s3.__str__())
        print(repr(s3))
    except TypeError as e:
        print(e)


if __name__ == "__main__":
    main()