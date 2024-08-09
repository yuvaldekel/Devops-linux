import tkinter as tk
#from tkinter import ttk 
import ttkbootstrap as ttk


def convert(input_var: tk.IntVar, output_var: tk.StringVar):
    miles = input_var.get()
    km = miles * 1.61
    output_var.set(f"Output: {km}")


def main():
    window = ttk.Window(themename='darkly')
    window.title("Demo")
    window.geometry('400x200')

    title_label = ttk.Label(window, text='Miles to kilometers', font='Calibri 24 bold')
    title_label.pack(pady=5)

    input_frame = ttk.Frame(window)

    input_var = tk.IntVar(input_frame)
    output_var = tk.StringVar()

    entry = ttk.Entry(input_frame, textvariable=input_var)
    button = ttk.Button(input_frame, text='Convert', command=lambda: convert(input_var, output_var))
    
    entry.pack(side='left', padx=10)
    button.pack(side='left')
    input_frame.pack(pady=10)

    output_label = ttk.Label(window,
                             font='Calibri 24',
                             textvariable=output_var)
    
    output_label.pack(pady=5)

    window.mainloop()


if __name__ == "__main__":
    main()