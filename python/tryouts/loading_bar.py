from math import sqrt
from random import seed, random
from termcolor import colored
from time import sleep
import webbrowser


def progress_bar(size = 40, step = 3):
    seed(2 * sqrt(step))

    try:
        print("\033[?25l", end = '')
        
        for curr_place in range(size + 1):
            percent = int(curr_place / size * 100)
            left = size - curr_place

            print(colored(f"PROGRESS: [{percent}%]", 'black', 'on_green'), end = '')
            print(f" [{'#' * curr_place}{"." * left}]\r", end = "")

            if curr_place % step == 0 or curr_place == size:
               sleep(random())
            
        print(f"{' ' * (size + 20)}\r", end = '')
    
    finally:
        print("\033[?25h", end = '')


def main():
    print("Wait for it...")
    progress_bar(step = 3)
    print("Opening")

    #sleep(0.5)
    #webbrowser.open("www.google.com")


if __name__ == "__main__":
    main()