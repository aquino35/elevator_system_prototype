import serial
import serial.tools.list_ports
import time
from queue import Queue # not being recognized
import threading
from multiprocessing.pool import ThreadPool
CONSTANT_BAUDRATE = 9600
CONSTANT_ARDUINO_COUNT = 2


class ElevatorManager:

    def __init__(self):

        self.initialize_containers()
        self.arduino_message_queue = Queue(maxsize = 20)
        self.port_list = serial.tools.list_ports.comports(include_links=False) # searches for all computer ports 
        self.detect_port() 
        #self.init_comm() # method for testing 


    def initialize_containers(self):

        try:
            self.arduino_list = [] # Container for arduinos
            self.eid_list = [] # Container for unique eids
            self.tid_container = []
            self.elevator_dictionary = {} # Dictionary to that has unique eid's to difference between conflictin eid's.
        except:
            print("Error initializing the Elevator Manager containers.\n")

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
            self.connect_arduinos(self.port1, self.port2, CONSTANT_BAUDRATE)
        except:
            print("Error detecting ports.\n")


    def connect_arduinos(self, port1, port2, baudrate):
        """ Connect pair of arduinos."""
        try:
            self.arduino_1 = serial.Serial(port1, baudrate)  # mega2560
            self.elevator_counter=+2 # 2 elevators in each arduino
            self.arduino_2 = serial.Serial(port2, baudrate)  # mega2560
            self.elevator_counter=+2 # 2 elevators in each arduino
            self.arduino_list.append(self.arduino_1) # appending arduino 1 on to the arduino container
            self.arduino_list.append(self.arduino_2) # appending arduino 2 to on to the arduino container
        except:
            print("Error connecting to an Arduino.\n")

        
    def init_comm(self):
        """ Dummy communication stablish to initially test the prototype """

        try:
            self.pool = ThreadPool(CONSTANT_ARDUINO_COUNT)
            for arduino in self.arduino_list:
                self.pool.apply_async(self.process_arduinos, (arduino,))
            self.pool.close()
            self.pool.join()
            eid = self.get_global_eid(arduino)
            print('{}\n'.format(eid)) 
            self.elevator_dictionary = {n: self.tid_container[n]  for n in range(CONSTANT_ARDUINO_COUNT)}
            print("The original dictionary : {}\n".format(self.elevator_dictionary)) 
        except:
            print("Error threading incoming arduinos.\n") 


    def process_arduinos(self, arduino):

        try:
            current_tid = threading.current_thread().ident 
            print(current_tid)         
            self.tid_container.append(current_tid)
            #print(self.tid_container)
            #if not (arduino.in_waiting): # only read if there is something waiting to be read, inWaiting is deprecated
            self.welcome_msg = arduino.readline()
            self.arduino_message_queue.put(self.welcome_msg.decode())
            print(self.welcome_msg.decode())
        except:
             print('Error processing {}.\n'.format(arduino))

    
    def get_global_eid(self, arduino_bin):

        try:
            total_bins = arduino_bin * (self.elevator_counter - 1)  # elevator bins (2)
            desired_bin = total_bins/self.elevator_counter # to get correct bin
            desired_elevator = total_bins%self.elevator_counter # to get specific elevator
            unique_eid = desired_elevator + desired_bin
            global_eid = self.elevator_dictionary['{}'.format(unique_eid)]
            self.eid_list.append(unique_eid)
                #print(result)
            #print(self.eid_list)
            print('{}\n'.format(global_eid))
            return global_eid
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