import serial

arduino = serial.Serial('/dev/cu.usbmodem14201', 9600)  # mega2560

def write_read(command):
    arduino.write(command)
    data = arduino.readline()
    return data

def comm_init():
    welcome_msg = arduino.readline()
    print(welcome_msg)
    while True:
        num = raw_input("Enter a command: ")
        final_command = write_read(num)
        print(final_command)
        #arduino.close()

comm_init()