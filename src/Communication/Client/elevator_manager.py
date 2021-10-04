import serial
import serial.tools.list_ports
import time
from queue import Queue # not being recognized
import threading
from multiprocessing.pool import ThreadPool
CONST_BAUDRATE = 9600
CONST_ARDUINO_COUNT = 2
CONST_ELEVATOR_COUNT = 4
CONST_EIDS = [0,1]



class ElevatorManager:

    def __init__(self):

        self.initialize_containers()
        self.arduino_message_queue = Queue(maxsize = 20)
        self.port_list = serial.tools.list_ports.comports(include_links=False) # searches for all computer ports 
        self.detect_port()
        self.elevator_count = 0 
        #self.init_comm() # method for testing 


    def initialize_containers(self):

        self.arduino_list = [] # Container for arduinos
        self.eid_list = [] # Container for unique eids
        self.tid_container = []
        self.unique_eids = {} # Dictionary to that has unique eid's to difference between conflicting eid's.


    def detect_port(self):
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


    def connect_arduinos(self, port1, port2, baudrate):
        """ Connect pair of arduinos."""
        try:
            self.arduino_1 = serial.Serial(port1, baudrate)  # mega2560
            self.arduino_2 = serial.Serial(port2, baudrate)  # mega2560
            self.arduino_list.append(self.arduino_1) # appending arduino 1 on to the arduino container
            self.arduino_list.append(self.arduino_2) # appending arduino 2 to on to the arduino container
        except:
            print("Error connecting to an Arduino.\n")

        
    def init_comm(self):
        """ Dummy communication stablish to initially test the prototype """

        try:
            self.pool = ThreadPool(CONST_ARDUINO_COUNT)
            for arduino in self.arduino_list:
                self.pool.apply_async(self.process_arduinos, (arduino,))
            self.pool.close()
            self.pool.join()
            self.create_unique_eids()
            self.get_global_eid()
            print("The original dictionary : {}\n".format(self.unique_eids))

        except:
            print("Error threading incoming arduinos.\n") 


    def process_arduinos(self, arduino):
        """ Subroutine inside each thread that excutes the UART protocol.
        MORE TO BE IMPLEMENTED.  """

        try:
            current_tid = threading.current_thread().ident 
            print(current_tid)         
            self.tid_container.append(current_tid)
            #if not (arduino.in_waiting): # only read if there is something waiting to be read, inWaiting is deprecated
            self.welcome_msg = arduino.readline()
            self.arduino_message_queue.put(self.welcome_msg.decode())
            print(self.welcome_msg.decode())
        except:
             print('Error processing {}.\n'.format(arduino))


    def create_unique_eids(self):

        self.unique_eids[0] = self.tid_container[0] + CONST_EIDS[0]
        self.unique_eids[1] = self.tid_container[0] + CONST_EIDS[1]
        self.unique_eids[2] = self.tid_container[1] + CONST_EIDS[0]
        self.unique_eids[3] = self.tid_container[1] + CONST_EIDS[1]


    #def get_global_eid(self, arduino_bin):
    def get_global_eid(self):

        try:
            # total_bins = arduino_bin * (CONST_ARDUINO_COUNT - 1)  # elevator bins (2)
            # desired_bin = total_bins/CONST_ARDUINO_COUNT # to get correct bin
            # desired_elevator = total_bins% CONST_ARDUINO_COUNT # to get specific elevator
            # unique_eid = desire d_elevator + desired_bin
            # global_eid = self.unique_eids['{}'.format(unique_eid)]
            # self.eid_list.append(unique_eid)
            #     #print(result)
            # #print(self.eid_list)
            # print('{}\n'.format(global_eid))
            # return global_eid
            for j in range(CONST_ELEVATOR_COUNT):
                m = j * (CONST_ELEVATOR_COUNT - 1)  # elevator bins (2)
                q = m/CONST_ELEVATOR_COUNT # to get correct bin
                r = m%CONST_ELEVATOR_COUNT # to get specific elevator
                result = r + q
                print(result)
                #print(self.unique_eids['{}'.format(result)]) # the money print

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