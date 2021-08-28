import serial
import time 
from cobs import cobs

class SerialMessage:

    serialChannel = None #pyserial API reference

    def __init__(self):

        self.msg = ""
        self.msgID = 1
        self.isFormed = False # indicates if the message structure is formed properly

    @classmethod
    def initializePort(cls):
        cls.serialChannel = serial.Serial('/dev/cu.usbmodem14201', 9600)  # (needs to find any kind of port) (soon)
    
    @classmethod
    def closePort(cls):
        cls.serialChannel.close()

    def verifyHeader():
        return None

    def retrieveHeader():
        return None
    
    def buildHeader():
        return None
    
    def recieveData():
        return None
    
    def retrieveData():
        return None

    @classmethod
    def transmitData(cls,msg):
        cls.serialChannel.write(msg.cobs.encode())