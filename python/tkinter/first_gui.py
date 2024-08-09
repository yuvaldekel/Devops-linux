from tkinter import *
from tkinter import ttk 


def main():
    window = Tk()
    window.title("Demo")
    window.geometry('300x150')

    title_label = ttk.Label(window, text='Miles to kilometers', font=('Calibri 24 bold'))

    window.mainloop()


if __name__ == "__main__":
    main()