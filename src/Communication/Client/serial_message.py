import serial
import time 
from cobs import cobs

import struct

class Serial_Message:

    serialChannel = None #pyserial API reference

    def __init__(self):
        self.msg = ""
        self.rx = bytes()
        self.eid = 1
        self.sid = 1
        self.buff = [] #will send info as bytes to the C++ side to be read

    @classmethod
    def initialize_port(cls):
        cls.serialChannel = serial.Serial('/dev/cu.usbmodem14201', 9600)  # (needs to find any kind of port) (soon)
    
    @classmethod
    def close_port(cls):
        cls.serialChannel.close()

    def verify_header(self):
        return None

    def retrieve_header(self):
        return None
    
    def build_header(self):
        '''Builds an encoded header for sending data.'''
        self.buff.append(bytes(self.msg, "utf-8")) #must encode strings before tightly packing
        self.buff.append(self.eid)
        self.buff.append(self.sid)
        
        packed_buf = struct.pack(str(len(self.msg)) + 's i i', *self.buff) #string is represented as array of characters, then we read two integers
        return packed_buf
        

    def recieve_data(self, data):
        self.rx = data.cobs.decode()
    
    def retrieve_data(self):
        return None

    @classmethod
    def transmit_data(cls,msg): #packed_buf should be passed here
        cls.serialChannel.write(msg.cobs.encode())