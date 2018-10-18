import serial

arduino = serial.Serial("COM4", 115200)



def send_command(flag, colorMsg):
    print(flag)
    if flag == True:
        print(b'1' + colorMsg.encode() + b'Q')
        arduino.write(b'1' + colorMsg.encode() + b'Q')
        answer = arduino.read_until(b'\n', 20)
        print(answer)
    elif flag == False:
        arduino.write(b'2Q')
        answer = arduino.read_until(b'\n', 20)
        print(answer)

def main():
    pass


if __name__ == '__main__':
    main()