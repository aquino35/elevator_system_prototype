import serial.tools.list_ports
from serial_message import SerialMessage
from queue import Queue # not being recognized
import threading
from multiprocessing.pool import ThreadPool
CONST_BAUDRATE = 9600
CONST_ARDUINO_COUNT = 2
CONST_ELEVATOR_COUNT = 2


class ElevatorManager:

    def __init__(self):

        self.initialize_containers()
        self.arduino_message_queue = Queue(maxsize = 20)
        self.port_list = serial.tools.list_ports.comports(include_links=False) # searches for all computer ports 
        self.initialize_arduino_ports()
        self.elevator_count = 0 
        self.rx_msg = SerialMessage()
        self.tx_msg = SerialMessage()
        #self.init_comm() # method for testing 


    def initialize_containers(self):

        self.arduino_channel_container = [] # Container for arduinos
        self.eid_container = [] # Container for unique eids
        self.tid_container = [] # Container for tids.
        self.aduino_thread_dict = {} # Dictionary to that has unique eid's to difference between conflicting eid's.


    def initialize_arduino_ports(self):
        """ Will automatically detect the two ports of the arduinos."""
        try:
            tmp = [] # temporary container for ports
            for port in self.port_list:
                #print('Find port '+ port.device)
                tmp.append(port.device)
            # macbook ports
            self.port1 = tmp[2] 
            self.port2 = tmp[3] 
            self.connect_arduinos(self.port1, self.port2, CONST_BAUDRATE)
   
        except:
            print("Error detecting ports.\n")

    def terminate_arduino_ports(self):
        """ Closes the two ports of the arduinos."""


    def connect_arduinos(self, port1, port2, baudrate):
        """ Connect pair of arduinos."""
        try:
            self.arduino_channel_1 = serial.Serial(port1, baudrate)  # mega2560
            self.arduino_channel_2 = serial.Serial(port2, baudrate)  # mega2560
            self.arduino_channel_container.append(self.arduino_channel_1) # appending arduino 1 on to the arduino container
            self.arduino_channel_container.append(self.arduino_channel_2) # appending arduino 2 to on to the arduino container
            self.assign_serial_channels(self.arduino_channel_1, self.arduino_channel_2)

        except:
            print("Error connecting to an Arduino.\n")


    def assign_serial_channels(self, arduino_channel_1, arduino_channel_2):
        """ This method assigns the incoming a arduino channels to a serial channel 
        container where it can later be used to read and write. """

        try:
            SerialMessage.serial_channel_container.append(arduino_channel_1)
            SerialMessage.serial_channel_container.append(arduino_channel_2)
            print(SerialMessage.serial_channel_container)
        except:
            print("Cannot assign serial channels")

        
    def init_comm(self):
        """ Dummy communication stablish to initially test the prototype """

        try:
            self.thread_pool = ThreadPool(CONST_ARDUINO_COUNT)
            for arduino_channel in self.arduino_channel_container:
                self.thread_pool.apply_async(self.process_arduinos, (arduino_channel,))
            self.thread_pool.close()
            self.thread_pool.join()
            self.create_unique_eids()
            self.get_global_eid(0)
            self.get_global_eid(1)
            self.get_global_eid(2)
            self.get_global_eid(3)
            #print("The original dictionary : {}\n".format(self.aduino_thread_dict))
        except:
            print("Error threading incoming arduinos.\n") 


    def process_arduinos(self, arduino_channel):
        """ Subroutine inside each thread that excutes the UART protocol.
        MORE TO BE IMPLEMENTED.  """

        try:
            current_tid = threading.current_thread().ident 
            #print(current_tid)         
            self.tid_container.append(current_tid)
            #if not (arduino.in_waiting): # only read if there is something waiting to be read, inWaiting is deprecated
            self.welcome_msg = arduino_channel.readline()
            self.arduino_message_queue.put(self.welcome_msg.decode("ascii", "ignore"))
            #print(self.welcome_msg.decode("ascii", "ignore"))
        except:
             print('Error processing {}.\n'.format(arduino_channel))


    def create_unique_eids(self):


        self.aduino_thread_dict[0] = self.tid_container[0]
        self.aduino_thread_dict[1] = self.tid_container[1] 


    def get_global_eid(self, global_eid):
        """ Uses modular arithmetic to get reference a specific arduino 
        to a specific elevator."""

        try:
            number_of_bins = global_eid * (CONST_ELEVATOR_COUNT - 1)  # elevator bins (2)
            desired_bin = number_of_bins/CONST_ELEVATOR_COUNT # to get correct bin
            desired_elevator = number_of_bins%CONST_ELEVATOR_COUNT # to get specific elevator
            #print(self.aduino_thread_dict[desired_bin],desired_elevator)
        except: 
            print("Cannot initialize four unique eid's.\n")

        
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