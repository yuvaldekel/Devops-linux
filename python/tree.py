def tree(size:int) -> None:

    if size % 2 == 0:
        raise ValueError("size is not compatible")

    for level in range(1,size+1,2):
        print(" " * ((size - level) // 2), end='')
        print("*" * level, end='')
        print(" " * ((size - level) // 2))


def main():
    tree(11)


if __name__ == "__main__":
    main()