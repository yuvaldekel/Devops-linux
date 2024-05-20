TOP_LEFT = (3,3)
SIZE = 4

def clac_steps(x,y):
    buttom_right =(3 +SIZE, 3 + SIZE)

    x_steps = 0
    y_steps = 0

    if x > buttom_right[0]:
        x_steps = x - buttom_right[0]
    if x < TOP_LEFT[0]:
        x_steps = TOP_LEFT[0] - x

    if y < TOP_LEFT[1]:
        y_steps = TOP_LEFT[1] - y
    if y > buttom_right[1]:
        y_steps = y - buttom_right[1]

    return y_steps + x_steps
    
def main():
    print(f"{clac_steps(1,1) = }")
    print(f"{clac_steps(5,2) = }")
    print(f"{clac_steps(9,1) = }")
    print(f"{clac_steps(10,4) = }")
    print(f"{clac_steps(10,10) = }")
    print(f"{clac_steps(5,8) = }")
    print(f"{clac_steps(1,10) = }")
    print(f"{clac_steps(1,5) = }")

if __name__ == "__main__":
    main()