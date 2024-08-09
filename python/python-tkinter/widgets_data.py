import tkinter as tk
#import tkinter.ttk as ttk
import ttkbootstrap as ttk

def button_func(entry_var: tk.StringVar, output_label: ttk.Label):
    output_label['text'] = entry_var.get()
    entry_var.set('')
    

def main():
    window = tk.Tk()
    window.title("Getting ans setting widgets")
    window.geometry("800x550")

    entry_var = tk.StringVar(window)

    label_widget = ttk.Label(window, text='This is a label')
    label_widget.pack(pady=5)

    entry_widget = ttk.Entry(window, textvariable=entry_var)
    entry_widget.pack(pady=5)

    output_widget = ttk.Label(window)
    button_widget = ttk.Button(window, text="A button", command=lambda: button_func(entry_var, output_widget))

    button_widget.pack(pady=5)
    output_widget.pack(pady=5)


    window.mainloop()


if __name__ == "__main__":
    main() 