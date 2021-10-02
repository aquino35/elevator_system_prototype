#!/usr/bin/env python

from tkinter import *
from tkinter import messagebox
from elevator_manager import Elevator_Manager


#MACROS DEFINITION FOR ELEVATOR SYSTEM APPLICATION:
GEOMETRY = '300x310'
TITLE = "Elevator System Prototype"
WELCOME_MSG = "Welcome to our prototype!"
FONT = "Helvetica"
ELEVATOR_REQUEST = "Request Elevator"
REQUEST_MSG = "An elevator will arrive shortly"
#KEYPAD MACROS:
LABEL_SIZE = 15
CURRENT_FLOOR_LABEL = "Current Floor:"
CURRENT_TEMPERATURE_LABEL = "Current Temp: "
CURRENT_WEIGHT_LABEL = "Current Label: "
OPEN_DOOR_LABEL = "Open Door" # change to OPEN_DOOR_LABEL
CLOSE_DOOR_LABEL = "Close Door"
MAINTENANCE_LABEL = "Maintenance" # change to maintenance_label
LOBBY_LABEL = "Lobby"
FIRST_FLOOR_LABEL = "1"
SECOND_FLOOR_LABEL = "2"
THIRD_FLOOR_LABEL = "3"
FOURTH_FLOOR_LABEL = "4"
FITH_FLOOR_LABEL = "5"
SIXTH_FLOOR_LABEL = "6"
SEVENTH_FLOOR_LABEL = "7"
EIGHTH_FLOOR_LABEL = "8"
NEIGH_FLOOR_LABEL = "9"
TENTH_FLOOR_LABEL = "10"
ELEVENTH_FLOOR_LABEL = "11"
TWELFTH_FLOOR_LABEL = "12"

OPEN_DOOR = 1 # related to door status
CLOSE_DOOR = 0 # related to door status
LOBBY = 0
FIRST_FLOOR = 1
SECOND_FLOOR = 2
THIRD_FLOOR = 3
FOURTH_FLOOR = 4
FITH_FLOOR = 5
SIXTH_FLOOR = 6
SEVENTH_FLOOR = 7
EIGHTH_FLOOR= 8
NEIGH_FLOOR = 9
TENTH_FLOOR = 10
ELEVENTH_FLOOR = 11
TWELFTH_FLOOR = 12