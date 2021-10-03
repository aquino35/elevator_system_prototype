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
        self.elev_manager = ElevatorManager()
        self.display_elevator_attr()
        self.build_keypad_layers()


    def build_keypad_layers(self):        
        """ Builds all the layers of the keypad."""

        self.build_first_keypad_layer()
        self.build_second_keypad_layer()
        self.build_third_keypad_layer()
        self.build_fourth_keypad_layer()
        self.build_fith_keypad_layer()
        self.build_sixth_keypad_layer()
        self.build_seventh_keypad_layer()

    def build_first_keypad_layer(self):
        """ Makes button for first layer of the keypad."""

        self.maintenance_button = self.create_button("maintenance_button", self.frame,
            MAINTENANCE_LABEL, self.get_elevator_maintenance_state, 4, 15)


    def build_second_keypad_layer(self):
        """ Makes buttons for second layer of the keypad."""

        self.open_door_button = self.create_button("open_door_button", self.frame,
            OPEN_DOOR_LABEL, self.open_elevator_door, 3, 6)
        self.close_door_button = self.create_button("close_door_button",self.frame,
            CLOSE_DOOR_LABEL, self.close_elevator_door, 4, 6)
        self.lobby_button = self.create_button("lobby_button", self.frame, LOBBY_LABEL, self.dummy, 5, 6)


    def build_third_keypad_layer(self):
        """ Makes buttons for third layer of the keypad."""

        self.f1_button = self.create_button("f1_button", self.frame, FIRST_FLOOR_LABEL, self.set_elevator_floor(FIRST_FLOOR), 3, 4)
        self.f2_button = self.create_button("f2_button", self.frame, SECOND_FLOOR_LABEL, self.set_elevator_floor(SECOND_FLOOR), 4, 4)
        self.f3_button = self.create_button("f3_button", self.frame, THIRD_FLOOR_LABEL, self.set_elevator_floor(THIRD_FLOOR), 5, 4)


    def build_fourth_keypad_layer(self):
        """ Makes buttons for fourth layer of the keypad."""

        self.f4_button = self.create_button("f4_button", self.frame, FOURTH_FLOOR_LABEL, self.set_elevator_floor(FOURTH_FLOOR), 3, 3)
        self.f5_button = self.create_button("f5_button", self.frame, FITH_FLOOR_LABEL, self.set_elevator_floor(FITH_FLOOR), 4, 3)
        self.f6_button = self.create_button("f6_button", self.frame, SIXTH_FLOOR_LABEL, self.set_elevator_floor(SIXTH_FLOOR), 5, 3)


    def build_fith_keypad_layer(self):
        """ Makes buttons for fith layer of the keypad."""

        self.f7_button = self.create_button("f7_button", self.frame, SEVENTH_FLOOR_LABEL, self.set_elevator_floor(SEVENTH_FLOOR), 3, 2)
        self.f8_button = self.create_button("f8_button", self.frame, EIGHTH_FLOOR_LABEL, self.set_elevator_floor(EIGHTH_FLOOR), 4, 2)
        self.f9_button = self.create_button("f9_button", self.frame, NEIGH_FLOOR_LABEL, self.set_elevator_floor(NEIGH_FLOOR), 5, 2)


    def build_sixth_keypad_layer(self):
        """ Makes buttons for sixth layer of the keypad."""

        self.f10_button = self.create_button("f10_button", self.frame, TENTH_FLOOR_LABEL, self.set_elevator_floor(TENTH_FLOOR_LABEL), 3, 1)
        self.f11_button = self.create_button("f11_button", self.frame, ELEVENTH_FLOOR_LABEL, self.set_elevator_floor(ELEVENTH_FLOOR_LABEL), 4, 1)
        self.f12_button = self.create_button("f12_button", self.frame, TWELFTH_FLOOR_LABEL, self.set_elevator_floor(TWELFTH_FLOOR_LABEL), 5, 1)
    
    def build_seventh_keypad_layer(self):
        """ Makes buttons for seventh layer of the keypad."""

        self.capacity_label = self.create_label(CAPACITY_LABEL, LABEL_SIZE, 1, 18)
        self.max_weight_label = self.create_label(MAXIMUM_WEIGHT_LABEL, LABEL_SIZE, 4, 18)


    def dummy(self):
        return


    def display_elevator_attr(self):        
        """ Display elevator attributes to the user."""

        self.elev_manager.display_elevator_attr()

        self.change_label(self.main_label,CURRENT_FLOOR_LABEL, LABEL_SIZE) # current floor
        self.label.grid(column=0, row=0) # changing the main label's grid location
        self.current_temperature_label = self.create_label(CURRENT_TEMPERATURE_LABEL, LABEL_SIZE, 0, 2) # current temp
        self.current_weight_label = self.create_label(CURRENT_WEIGHT_LABEL, LABEL_SIZE, 0, 3) # current weight
        self.person_count_label = self.create_label(PERSON_COUNT_LABEL, LABEL_SIZE, 0, 4) # current person count
        # tests
        self.elev_manager.init_comm()
        self.arduino_test_msg = self.elev_manager.arduino_message_queue.pop()
        print(self.arduino_test_msg)
        self.arduino_test = self.create_label(self.arduino_test_msg, LABEL_SIZE, 1, 1)


    def open_elevator_door(self):
        """ Calls the manager to open the door."""

        self.elev_manager.set_elevator_door_status()
    

    def close_elevator_door(self):
        self.elev_manager.set_elevator_door_status()
    

    def set_elevator_floor(self, floor):

        self.elev_manager.set_elevator_floor(floor)
    

    def get_elevator_lobby(self):

        self.elev_manager.get_elevator_lobby()
    

    def get_elevator_maintenance_state(self):
        
        self.elev_manager.get_elevator_maintenance_state()

