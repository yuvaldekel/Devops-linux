class t:
    def __init__(self) -> None:
        self.a = [5]
        self.b = 10
        self.c = 15
        self.index = 0

    def __iter__(self):
        self.index = 0
        return self
    
    def __next__(self):
        if self.index < 3:
            if self.index == 0:
                self.index +=1
                return self.a
            if self.index == 1:
                self.index +=1
                return self.b
            if self.index == 2:
                self.index +=1
                return self.c
        else:
            raise StopIteration
    
def main():
    t1 = t()
    for n in t1:
        print(n)

    print([5] in t1)
if __name__ == "__main__":
    main()