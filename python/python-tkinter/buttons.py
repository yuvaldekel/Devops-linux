import tkinter as tk
import tkinter.ttk as ttk
import ttkbootstrap as ttk


def main():
    window = tk.Tk()
    window.title('buttons')
    window.geometry('800x600')

    button_var = tk.StringVar(window, value='A button')
    button = ttk.Button(window,
                        text='A simple button',
                        command=lambda: print("a basic button"),
                        textvariable=button_var)
    button.pack(pady=5)

    check_var = tk.IntVar()
    check1 = ttk.Checkbutton(window,
                            text='checkbox 1',
                            command=lambda: print(check_var.get()),
                            variable=check_var,
                            onvalue=10,
                            offvalue=5)
    check1.pack()

    radio_var = tk.StringVar()
    radio1 = ttk.Radiobutton(window,
                             text="Radiobutton1",
                             value=5,
                             variable=radio_var,
                             command=lambda: print(radio_var.get()))
    radio1.pack()

    radio2 = ttk.Radiobutton(window,
                             text="Radiobutton2",
                             value='radio1',
                             variable=radio_var,
                             command=lambda: print(radio_var.get()))
    radio2.pack()


    check_var2 = tk.StringVar(value='Off')
    radio_var2 = tk.StringVar()

    radio_ex1 = ttk.Radiobutton(window,
                            text="Radiobutton_ex1",
                            value='radio1',
                            variable=radio_var2,
                            command=lambda: check_var.set('Off'))
    radio_ex1.pack()

    radio_ex2 = ttk.Radiobutton(window,
                            text="Radiobutton_ex2",
                            value='radio2',
                            variable=radio_var2,
                            command=lambda: check_var.set('Off'))
    radio_ex2.pack()
    
    check1 = ttk.Checkbutton(window,
                            offvalue="Off",
                            onvalue="On",
                            text='checkbox 1',
                            variable=check_var2)
    check1.pack()

    label_check = ttk.Label(window,
                            textvariable=check_var2)
    label_check.pack()
    label_radio = ttk.Label(window,
                            textvariable=radio_var2)
    label_radio.pack()

    window.mainloop()


if __name__ == "__main__":
    main()