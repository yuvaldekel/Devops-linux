import tkinter as tk
import tkinter.ttk as ttk


def button_func():
    print("The button was pressed")


def main():
    window = tk.Tk()
    window.title("Window and widgets")
    window.geometry("800x550")

    label_widget = ttk.Label(window, text='This is a text')
    label_widget.pack(pady=5)

    text_widget = tk.Text(window)
    text_widget.pack(pady=5)

    entry_widget = ttk.Entry(window)
    entry_widget.pack(pady=5)

    button_widget = ttk.Button(window, text="A button", command=button_func)
    button_widget.pack(pady=5)

    window.mainloop()


if __name__ == "__main__":
    main() 