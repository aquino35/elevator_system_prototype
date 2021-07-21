import serial

arduino = serial.Serial('/dev/cu.usbmodem14201', 9600)  # mega2560

def arduino_comm(command):
    arduino.write(command)
    data = arduino.readline()
    return data

def init_comm():
    welcome_msg = arduino.readline()
    print(welcome_msg)
    while True:
        num = input("Enter a command: ")
        final_command = arduino_comm(num.encode())
        print(final_command.decode())
        #arduino.close()

init_comm()