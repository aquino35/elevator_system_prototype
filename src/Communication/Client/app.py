#!/usr/bin/env python   
# from .app_macros import *  #relative import - did not work properly
from app_macros import *


class App():

    def __init__(self,):
        """ App's constructor."""

        self.init_app()

    def init_app(self):
        """ Initializes the App. """

        self.setup_app()
        self.main_label = self.create_label(WELCOME_MSG, 25, 5, 5)
        self.elevator_request_button = self.create_button("elevator_request_button", 
            self.frame, ELEVATOR_REQUEST, self.build_elevator_keypad, 5, 8)
        self.run_app() # runs app on a loop


    def setup_app(self):
        """ Sets the App's frame and title. """

        self.frame = Tk() # Creating main window application
        self.frame.geometry(GEOMETRY) # Setting size of the application's frame.
        self.frame.title(TITLE) # Assigning the application a title.
    

    def create_button(self, button_name, frame, txt, cb, _col, _row):
        """ Makes a button. """

        button_name = Button(frame, text=txt, command=cb)
        button_name.grid(column=_col, row=_row )
        return button_name

    def run_app(self):
        """ Runs the App. """

        self.frame.mainloop()


    def destroy_button(self, button_name):
        """ Destroy a button in the App. """

        button_name.destroy()


    def create_label(self, txt, size, _col, _row):
        """ Set the App's main label. """

        self.label = Label(self.frame, text=txt, font=(FONT, size))
        self.label.grid(column= _col, row= _row)
        return self.label

        
    def change_label(self, label, txt, size):
        """ Changes App's main label. Note: Does not change grid. """

        self.label.configure(text=txt, font=(FONT, size)) 

    
    def terminate_app(self):
        """ Changes App's main label."""

        return


    def display_info(self, info):
        """ Display pop-up information of the elevator system."""

        messagebox.showinfo(TITLE, info) 


    def display_warning(self, info):
        """ Display pop-up warnings of the elevator system."""

        messagebox.showwarning(TITLE, info) 


    def display_error(self, info):
        """ Display pop-up errors of the elevator system."""

        messagebox.showerror(TITLE, info) 
    

    # Next up we can see our callbacks defined for the buttons

    def build_elevator_keypad(self):
        """ Command that builds the keypad of the elevator system."""

        self.destroy_button(self.elevator_request_button) # destroy the request button
        self.display_info(REQUEST_MSG) # alert user that an elevator is on its way.
        # creating the elevator's keypad:
        self.change_label(self.main_label,CURRENT_FLOOR, 15)
        self.label.grid(column=1, row=0) # changing the main label's grid location
        self.elev_manager = Elevator_Manager()
        self.tupple = self.elev_manager.init_comm()
        self.arduino_test = self.create_label(self.tupple[0], 15, 3, 0)
        self.build_keypad_layers()
        """"self.elev_manager.get_elevator_floor(FIRST_FLOOR) # EJEMPLO PARA ANA"""
        self.create_label(CURRENT_TEMPERATURE, 15, column=1, row= 1)  
        self.create_label(CURRENT_WEIGHT, 15, column=1, row= 2)

    def build_keypad_layers(self):        
        """ Builds all the layers of the keypad."""

        self.build_first_keypad_layer()
        self.build_second_keypad_layer()
        self.build_third_keypad_layer()
        self.build_fourth_keypad_layer()
        self.build_fith_keypad_layer()
        self.build_sixth_keypad_layer()

    def build_first_keypad_layer(self):
        """ Makes button for first layer of the keypad."""

        self.maintenance_button = self.create_button("maintenance_button", self.frame,
            MAINTENANCE, self.get_elevator_maintenance_state, 3, 18)


    def build_second_keypad_layer(self):
        """ Makes buttons for second layer of the keypad."""

        self.open_door_button = self.create_button("open_door_button", self.frame,
            OPEN_DOOR, self.open_elevator_door, 1, 15)
        self.close_door_button = self.create_button("close_door_button",self.frame,
            CLOSE_DOOR, self.close_elevator_door, 3, 15)
        self.lobby_button = self.create_button("lobby_button", self.frame, LOBBY, self.dummy, 5, 15)


    def build_third_keypad_layer(self):
        """ Makes buttons for third layer of the keypad."""

        self.f1_button = self.create_button("f1_button", self.frame, FIRST_FLOOR, self.set_elevator_floor(FIRST_FLOOR), 1, 12)
        self.f2_button = self.create_button("f2_button", self.frame, SECOND_FLOOR, self.set_elevator_floor(SECOND_FLOOR), 3, 12)
        self.f3_button = self.create_button("f3_button", self.frame, THIRD_FLOOR, self.set_elevator_floor(THIRD_FLOOR), 5, 12)


    def build_fourth_keypad_layer(self):
        """ Makes buttons for fourth layer of the keypad."""

        self.f4_button = self.create_button("f4_button", self.frame, FOURTH_FLOOR, self.set_elevator_floor(FOURTH_FLOOR), 1, 9)
        self.f5_button = self.create_button("f5_button", self.frame, FITH_FLOOR, self.set_elevator_floor(FITH_FLOOR), 3, 9)
        self.f6_button = self.create_button("f6_button", self.frame, SIXTH_FLOOR, self.set_elevator_floor(SIXTH_FLOOR), 5, 9)


    def build_fith_keypad_layer(self):
        """ Makes buttons for fith layer of the keypad."""

        self.f7_button = self.create_button("f7_button", self.frame, SEVENTH_FLOOR, self.set_elevator_floor(SEVENTH_FLOOR), 1, 6)
        self.f8_button = self.create_button("f8_button", self.frame, EIGHTH_FLOOR, self.set_elevator_floor(EIGHTH_FLOOR), 3, 6)
        self.f9_button = self.create_button("f9_button", self.frame, NEIGH_FLOOR, self.set_elevator_floor(NEIGH_FLOOR), 5, 6)


    def build_sixth_keypad_layer(self):
        """ Makes buttons for sixth layer of the keypad."""

        self.f10_button = self.create_button("f10_button", self.frame, TENTH_FLOOR, self.set_elevator_floor(TENTH_FLOOR), 1, 3)
        self.f11_button = self.create_button("f11_button", self.frame, ELEVENTH_FLOOR, self.set_elevator_floor(ELEVENTH_FLOOR), 3, 3)
        self.f12_button = self.create_button("f12_button", self.frame, TWELFTH_FLOOR, self.set_elevator_floor(TWELFTH_FLOOR), 5, 3)
    

    def open_elevator_door(self):
        self.elev_manager.set_elevator_door_status()
    
    def close_elevator_door(self):
        self.elev_manager.set_elevator_door_status()
    
    def set_elevator_floor(self, floor):
        self.elev_manager.set_elevator_floor(floor)
    
    def get_elevator_lobby(self):
        self.elev_manager.get_elevator_lobby()
    
    def get_elevator_maintenance_state(self):
        self.elev_manager.get_elevator_maintenance_state()





