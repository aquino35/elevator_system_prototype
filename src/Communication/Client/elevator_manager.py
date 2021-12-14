from serial.serialutil import EIGHTBITS
import serial.tools.list_ports
import serial #pyserial
from time import time, sleep
from cobs import cobs       # for encoding
import threading

BAUDRATE                =   9600
ARDUINO_COUNT           =   2
SERVER_COUNT            =   2
ELEVATOR_COUNT          =   2
QUEUE_SIZE              =   255

COBS_DELIMITER           =   b'\0' # COBS 1-byte delimiter is hex zero as a (binary) bytes character
STD_ENCODE_SIZE          =   14
STD_DECODE_SIZE          =   14

EID_OFFSET               =   1
SID_OFFSET               =   2
DOOR_OFFSET              =   3
LIGHT_OFFSET             =   4
FLOOR_OFFSET             =   5
TEMP_OFFSET              =   6
LOAD_OFFSET              =   7
PERSON_OFFSET            =   8
MAINTENANCE_OFFSET       =   9
DIRECTION_OFFSET         =   10
MOVING_OFFSET            =   11
MSG_OFFSET               =   12


WELCOME_MSG = "Welcome to the elevator system Prototype"
IDLE_MSG = "Elevator is in Idle State"
MOVING_MSG = "Elevator is in Moving State!"
EMERGENCY_MSG = "Elevator has entered Emergency State!"
ENERGY_SAVING_MSG = "Elevator is entering energy saving mode!"
msgs_dict = {0:WELCOME_MSG, 1:IDLE_MSG, 2:MOVING_MSG, 3:EMERGENCY_MSG, 4:ENERGY_SAVING_MSG}


class ElevatorManager:


    def __init__(self):

        self.initialize_containers()
        self.init_elev_attrs()
        #self.arduino_message_queue = Queue(maxsize = 20)
        self.port_list = serial.tools.list_ports.comports(include_links=False) # searches for all computer ports 
        self.initialize_arduino_ports()
        #self.connect_to_servers() # method for testing 


    def initialize_containers(self) -> None:

        self.eid_list = []              # Container for unique eids
        self.tid_list = []              # Container for tids.
        self.serial_channel_list = []
        self.aduino_thread_dict = {}    # Dictionary to that has unique eid's to difference between conflicting eid's.


    def init_elev_attrs(self) -> None:

        self.eid = 0
        self.sid = 0
        self.door_status = 0
        self.light_status = 0
        self.current_floor = 0
        self.temp = 0
        self.load = 0
        self.person_counter  = 0
        self.maintenance  = 0
        self.direction  = 0
        self.moving  = 0
        self.msg_to_user  = 0


    def initialize_arduino_ports(self) -> None:
        """ Automatically detect the ports of the arduinos."""
        try:
            temp = [] # temporary container for ports
            for port in self.port_list:
                #print('Find port '+ port.device)
                temp.append(port.device)
            # macbook ports
            self.port1 = temp[2] 
            self.port2 = temp[3] 
            self.connect_arduinos(self.port1, self.port2, BAUDRATE)
   
        except:
            print("Error detecting ports.\n")


    def terminate_arduino_ports(self):
        """ Closes the two ports of the arduinos."""


    def connect_arduinos(self, port1: None, port2: None, baudrate=EIGHTBITS)-> None:
        """ Connect pair of arduinos."""
        try:
            self.arduino_serial_channel_1 = serial.Serial(port1, baudrate)  # mega2560
            self.arduino_serial_channel_2 = serial.Serial(port2, baudrate)  # mega2560
            self.assign_serial_channels(self.arduino_serial_channel_1, self.arduino_serial_channel_2)

        except:
            print("Error connecting to an Arduino.\n")


    def assign_serial_channels(self, arduino_1:serial.Serial, arduino_2:serial.Serial) -> None:
        """ This method assigns the incoming a arduino channels to a serial channel 
        container where it can later be used to read and write. """

        try:
            self.serial_channel_list.append(arduino_1)
            self.serial_channel_list.append(arduino_2)
            print(self.serial_channel_list)
        except:
            print("Cannot assign serial channels")

        
    def connect_to_servers(self) -> None:
        """ Dummy communication stablish to initially test the prototype """
        

        self.arduino_t1 = threading.Thread(target= self.process_arduinos, args = (self.serial_channel_list[0],))
        self.arduino_t2 = threading.Thread(target= self.process_arduinos, args = (self.serial_channel_list[1],))

        self.arduino_t1.start()
        self.arduino_t2.start()

        self.arduino_t1.join()
        self.arduino_t2.join()


    def process_arduinos(self, arduino:serial.Serial) -> None:
        """ Subroutine inside each thread that excutes the UART protocol.
        MORE TO BE IMPLEMENTED.  """

        while(1):

            current_tid = threading.current_thread().ident 
            print(current_tid)          
            self.tid_list.append(current_tid)


            self.serial_service_rx(arduino)

            self.request = self.initialize_cobs_pkt_list(self.eid, self.sid, 
                            self.door_status, self.light_status, 
                            self.current_floor, self.temp, self.load, self.person_counter, 
                            self.maintenance, self.direction, self.moving, self.msg_to_user)

            self.serial_service_tx(arduino, self.request)
            sleep(0.5)


    def create_unique_eids(self) -> None:

        self.aduino_thread_dict[0] = self.tid_list[0]
        self.aduino_thread_dict[1] = self.tid_list[1] 


    def get_global_eid(self, global_eid:int) -> None:
        """ Uses modular arithmetic to get reference a specific arduino 
        to a specific elevator."""

        try:
            number_of_bins = global_eid * (ELEVATOR_COUNT - 1)  # elevator bins (2)
            desired_bin = number_of_bins/ELEVATOR_COUNT # to get correct bin
            desired_elevator = number_of_bins%ELEVATOR_COUNT # to get specific elevator
            #print(self.aduino_thread_dict[desired_bin],desired_elevator)
        except: 
            print("Cannot initialize four unique eid's.\n")


    def initialize_cobs_pkt_list(self,*kwargs:tuple) -> None:

        cobs_pkt_list = []

        for elevator_attr in kwargs:
            cobs_pkt_list.append(elevator_attr)

        print("Cobs container:", cobs_pkt_list)

        return cobs_pkt_list


    def cobs_encode(self, pkt:bytes) -> None:

        encoded_pkt = cobs.encode(pkt)
        encoded_pkt += COBS_DELIMITER
        return encoded_pkt


    def cobs_decode(self, serial_channel:serial.Serial, pkt_size:int) -> list:
            
        time_to_decode = 1
        start = time()
        byte_counter = 0
        encoded_pkt = bytearray()


        while time() - start < time_to_decode:

            # Wait until all bytes are in pyserial rx buffer
            if serial_channel.in_waiting:

                # read bytes
                if byte_counter<pkt_size:

                    bit = serial_channel.read()
                    byte_counter +=1
                    encoded_pkt+= bit
                    print("Encoded Byte", encoded_pkt)

                    if bit == b'\xff': # if cobs delimeter found
                        decoded_pkt = list(encoded_pkt)
                        print(decoded_pkt)
                        byte_counter = 0;
                        return decoded_pkt


    def extract_pkt_data(self, pkt:list) -> None:

        self.eid = pkt[EID_OFFSET]
        self.sid = pkt[SID_OFFSET]
        self.door_status = pkt[DOOR_OFFSET]
        self.light_status = pkt[LIGHT_OFFSET]
        self.current_floor = pkt[FLOOR_OFFSET]
        self.temp = pkt[TEMP_OFFSET]
        self.load = pkt[LOAD_OFFSET]
        self.person_counter  = pkt[PERSON_OFFSET]
        self.maintenance  = pkt[MAINTENANCE_OFFSET]
        self.direction  = pkt[DIRECTION_OFFSET]
        self.moving  = pkt[MOVING_OFFSET]
        self.msg_to_user  = pkt[MSG_OFFSET]


    def serial_service_rx(self, serial_channel:serial.Serial) -> None:


        decoded_pkt = self.cobs_decode(serial_channel, STD_DECODE_SIZE)

        #testing stuff 
        print(decoded_pkt[EID_OFFSET])
        print(decoded_pkt[SID_OFFSET])
        print(decoded_pkt[DOOR_OFFSET])
        print(decoded_pkt[LIGHT_OFFSET])
        print(decoded_pkt[FLOOR_OFFSET])
        print(decoded_pkt[TEMP_OFFSET])
        print(decoded_pkt[LOAD_OFFSET])
        print(decoded_pkt[PERSON_OFFSET])
        print(decoded_pkt[MAINTENANCE_OFFSET])
        print(decoded_pkt[DIRECTION_OFFSET])
        print(decoded_pkt[MOVING_OFFSET])
        print(decoded_pkt[MSG_OFFSET])
        msg = decoded_pkt[MSG_OFFSET]
        print(msgs_dict[msg])

        self.extract_pkt_data(decoded_pkt)


    def serial_service_tx(self, serial_channel:serial.Serial, pkt:list) -> None:

        cobs_pkt = bytearray(pkt)
        service = self.cobs_encode(cobs_pkt)
        serial_channel.write(service)
        serial_channel.flush()
        print("Service request:",service)


    def display_elevator_attr(self):
        """ Return attributes of a designated elevator to display to the user. """
        self.get_door_status()
        self.get_light_status()
        self.get_floor()
        self.get_temp()
        self.get_load()
        return 


    # have to verify 
    def get_eid(self) -> int:
        """ Return eid of a designated elevator to display to the user. """

        return self.eid


    def get_sid(self) -> int:
        return self.sid


    def get_door_status(self) -> int:
        return self.door_status


    def get_light_status(self) -> int:
        return self.light_status


    def get_floor(self) -> int:
        return self.current_floor


    def get_temp(self) -> int:
        return self.temp


    def get_load(self) -> int:
        return self.load


    def get_msg_to_user(self) -> int:
        return self.msg_to_user

        
    def set_eid(self, eid:int) -> None:
        self.eid = eid


    def set_sid(self, sid)-> None:
        self.sid = sid


    def set_door_status(self, door_status:int) -> None:
        self.door_status = door_status


    def set_light_status(self, light_status:int) -> None:
        self.light_status = light_status


    def set_floor(self, current_floor:int) -> None:
        self.current_floor = current_floor


    def set_temp(self, temp:int) -> None:
        self.temp = temp


    def set_load(self, load:int) -> None:
        self.load = load


    def set_msg_to_user(self, msg_to_user:int) -> None:
        self.msg_to_user = msg_to_user

    
manager = ElevatorManager()
manager.connect_to_servers() # testing