import serial
import time 
from cobs import cobs

class Serial_Message:

    serialChannel = None #pyserial API reference

    def __init__(self):

        self.msg = ""
        self.eid = 1
        self.sid = 1

    @classmethod
    def initialize_port(cls):
        cls.serialChannel = serial.Serial('/dev/cu.usbmodem14201', 9600)  # (needs to find any kind of port) (soon)
    
    @classmethod
    def close_port(cls):
        cls.serialChannel.close()

    def verify_header():
        return None

    def retrieve_header():
        return None
    
    def build_header():
        return None
    
    def recieve_data():
        return None
    
    def retrieve_data():
        return None

    @classmethod
    def transmit_data(cls,msg):
        cls.serialChannel.write(msg.cobs.encode())