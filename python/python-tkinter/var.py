import tkinter as tk
import tkinter.ttk as ttk
#import ttkbootstrap as ttk


def button_func(string_var: tk.StringVar):
    print(string_var.get())
    string_var.set("Button pressed")


def main():
    window = tk.Tk()
    window.title("Tkinter Variables")
    window.geometry("800x600")

    string_var = tk.StringVar(window, value='start')

    entry = ttk.Entry(window, textvariable=string_var)
    entry.pack()

    label = ttk.Label(window, textvariable=string_var)    
    label.pack(pady=5)

    button = ttk.Button(window,
                        text='button',
                        command=lambda: button_func(string_var))
    button.pack(pady=5)

    

    window.mainloop()




if __name__ == "__main__":
    main()