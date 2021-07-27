import serial

arduino = serial.Serial('/dev/cu.usbmodem14201', 9600)  # mega2560

def arduino_comm(command):
    arduino.write(command)
    data = arduino.readline()
    return data

def init_comm():
    welcome_msg = arduino.readline()
    print(welcome_msg.decode())
    while True:
        msg = input("Enter a key to open the door: ")
        final_command = arduino_comm(msg.encode())
        print(final_command.decode())
        msg = input("Enter a key to see current state of Elevator: ")
        final_command = arduino_comm(msg.encode())
        print(final_command.decode())
        msg = input("Enter a key to change to Idle state: ")
        final_command = arduino_comm(msg.encode())
        print(final_command.decode())
        msg = input("Enter a number to load the elevator: ")
        final_command = arduino_comm(msg.encode())
        print(final_command.decode())
        msg = input("Enter a key to unload the elevator: ")
        final_command = arduino_comm(msg.encode())
        print(final_command.decode())
        #arduino.close()

init_comm()