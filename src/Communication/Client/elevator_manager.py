import serial
import serial.tools.list_ports
import time
import Queue # not being recognized
from multiprocessing.pool import ThreadPool
BAUDRATE = 9600
POOL_SIZE = 2

class ElevatorManager:

    def __init__(self):

        self.arduino_list = [] # container for arduinos
        self.arduino_message_queue = [] 
        self.port_list = serial.tools.list_ports.comports(include_links=False)
        self.detect_port() 
        #self.init_comm() # method for testing 

    def detect_port(self):
        """ Will automatically detect the two ports of the arduinos."""

        tmp = [] # temporary container for ports
        for port in self.port_list:
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
        """ Dummy communication stablish to initially test the prototype """

        self.pool = ThreadPool(POOL_SIZE)
        for arduino in self.arduino_list:
            self.pool.apply_async(self.processArduinos, (arduino,))
        self.pool.close()
        self.pool.join()


    def processArduinos(self, arduino):

        try:
            if not (arduino.in_waiting): # only read if there is something waiting to be read, inWaiting is deprecated
                self.welcome_msg = arduino.readline()
                print(self.welcome_msg.decode())
                self.arduino_message_queue.append(self.welcome_msg.decode())
        except:
            print('Error handling arduino')

    
    def display_elevator_attr(self):
        """ Return an attribute of a designated elevator to display to the user. """

        return 


    def get_elevator_floor(self):
        """ Return the floor of the designated elevator """

        return


    def get_elevator_lobby(self):
        """ opens the floor of the designated elevator """
        return

    
    def get_elevator_maintenance_state(self):
        """ Return the maintenance state of the designated elevator """

        return

        
    def get_elevator_temperature(self):
        """ Returns current temperature of the designated elevator """

        return

    
    def get_elevator_capacity(self):
        """ Returns current temperature of the designated elevator """

        return


    def set_elevator_floor(self, floor):
        """ Sets the floor of the designated elevator """

        return


    def set_elevator_temperature(self, floor):
        """ Returns current temperature of the designated elevator """

        return


    def set_elevator_door_status(self):
        """ Open or Close the door of the designated elevator  """

        return
    
#Elevator_Manager()