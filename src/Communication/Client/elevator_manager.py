import serial
import serial.tools.list_ports
BAUDRATE = 9600

class Elevator_Manager:

    def __init__(self):

        self.arduino_list = [] # container for arduinos
        self.port_finder = serial.tools.list_ports.comports(include_links=False)
        self.detect_port() 
        #self.init_comm() # method for testing 

    def detect_port(self):
        """ Will automatically detect the two ports of the arduinos."""
        tmp = [] # temporary container for ports
        for port in self.port_finder:
            #print('Find port '+ port.device)
            tmp.append(port.device)

        # macbook ports
        self.port1 = tmp[2] 
        self.port2 = tmp[3] 
        self.connect_arduinos(self.port1, self.port2, BAUDRATE)

    def connect_arduinos(self, port1, port2, baudrate):
        """ Connect pair of arduinos."""

        self.arduino_1 = serial.Serial(port1, baudrate)  # mega2560
        self.arduino_2 = serial.Serial(port2, baudrate)  # mega2560
        self.arduino_list.append(self.arduino_1) # appending arduino 1 on to the arduino container
        self.arduino_list.append(self.arduino_2) # appending arduino 2 to on to the arduino container

    def init_comm(self):

        if not (self.arduino_1.in_waiting or self.arduino_2.in_waiting): # only read if there is something waiting to be read, inWaiting is deprecated
            welcome_msg = self.arduino_1.readline()
            welcome_msg1 = self.arduino_2.readline()
            print(welcome_msg.decode())
            print(welcome_msg1.decode())
        return welcome_msg, welcome_msg1


#Elevator_Manager()