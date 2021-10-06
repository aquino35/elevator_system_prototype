import time 
import serial
from cobs import cobs
import app_macros
import struct
from app_macros import EID_OFFSET, SID_OFFSET, AID_OFFSET


class SerialMessage:


    serial_channel_container = [] #class container holding both pyserial API references


    def __init__(self):

        self.initialize_msg_attr()


    def initialize_msg_attr(self):

        self.aid = 0
        self.eid = 0
        self.sid = 0
        self.buff = [] #will send info as bytes to the C++ side to be read


    def verify_header(self):
        return None


    def retrieve_header(self):
        return None
    

    def build_header(self):
        '''Builds an encoded header for sending data.'''

        self.buff = [self.eid, self.sid, self.aid]


    def encode(self):
        self.buff.append(bytes(self.buff[AID_OFFSET]), "utf-8") #must encode strings before tightly packing
        
        packed_buf = struct.pack(str(len(self.buff[AID_OFFSET])) + 's i i', *self.buff) #string is represented as array of characters, then we read two integers
        return packed_buf


    def recieve_data(self, data):
        self.rx = data.cobs.decode()
    

    def retrieve_data(self):
        return None


    @classmethod
    def transmit_data(cls,msg): #packed_buf should be passed here

        for serial_channel in serial_channel_container:
            cls.serial_channel.write(msg.cobs.encode())

