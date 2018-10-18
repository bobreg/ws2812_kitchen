from tkinter import *
import send_command433

flag = False
Red = 0
Green = 0
Blue = 0
colorMsg = str(int('%02x%02x%02x' % (Red, Green, Blue), 8)) # это передаём в ардуино в виде кодов цвета
print(colorMsg)
color = "#{:02x}{:02x}{:02x}".format(Red, Green, Blue)  # это для конвертации кодов цвета в формат #ffffff для
                                                       # изменения цвета в окошке (RGBtoHEX_RGBMsg():)


def button1_vkl():
    global color
    global flag
    flag = True
    RGBtoHEX_RGBMsg()
    send_command433.send_command(flag, colorMsg)


def button2_vikl():
    global color
    global flag
    flag = False
    RGBtoHEX_RGBMsg()
    send_command433.send_command(flag, colorMsg)


def send_color_from_entry():
    global color_HEX
    global colorMsg
    global flag
    print(color_HEX.get())
    colorMsg = str(int(color_HEX.get(), 16))
    flag = True
    send_command433.send_command(flag, colorMsg)


def scaleR(value):
    global Red
    global flag
    flag = True
    Red = int(value)     # int важно для переменной color. Т.к. value - string
    RGBtoHEX_RGBMsg()


def scaleG(value):
    global Green
    global flag
    flag = True
    Green = int(value)
    RGBtoHEX_RGBMsg()


def scaleB(value):
    global Blue
    global flag
    flag = True
    Blue = int(value)
    RGBtoHEX_RGBMsg()


def RGBtoHEX_RGBMsg():
    global Red
    global Green
    global Blue
    global color
    global colorMsg
    colorMsg = str(int('%02x%02x%02x' % (Red, Green, Blue), 16))
    color ="#{:02x}{:02x}{:02x}".format(Red, Green, Blue)
    kvadrat['bg'] = color


# Создание окна
window = Tk()
window.title("Ответ от ардуино")
window.geometry("450x300")


buttuon1 = Button(text="Включить свет", width=20, height=3, command=button1_vkl)
buttuon2 = Button(text="Выключить свет", width=20, height=3, command=button2_vikl)
buttuon3 = Button(text="Отправить цвет", font='arial 7', command=send_color_from_entry)
buttuon1.place(x=25, y=220)
buttuon2.place(x=225, y=220)
buttuon3.place(x=350, y=100)


scaleR = Scale(window, orient=HORIZONTAL, length=300, from_=0, to=255,
               resolution=5, label='Добавить красного', relief='ridge', command=scaleR)
scaleG = Scale(window, orient = HORIZONTAL, length=300, from_=0, to=255,
               resolution=5, label='Добавить зелёного', relief='ridge', command=scaleG)
scaleB = Scale(window, orient = HORIZONTAL, length=300, from_=0, to=255,
               resolution=5, label = 'Добавить синего', relief = 'ridge', command=scaleB)
scaleR.place(x=25, y=20)
scaleG.place(x=25, y=90)
scaleB.place(x=25, y=160)


kvadrat = Canvas(window, width=30, height=30, bg=color)
kvadrat.place(x=350, y=20)


color_HEX = StringVar()


editColor = Entry(width='6', textvariable=color_HEX)
editColor.place(x=350, y=60)


window.mainloop()