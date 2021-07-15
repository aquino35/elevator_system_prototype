/*
 * TODO : DOCUMENT
 * 
 * 
 */
#include "elevator_system.h"

class Elevator: private System {
    
    public:

        bool isDoor_status() {
            return door_status;
            }

        void setDoor_status(bool door_status) {
            door_status = door_status; 
            }

        double getLoad_weight() {
            return load_weight;
            }

        void setLoad_weight(double load_weight) {
            load_weight = load_weight; 
            }

        int getFloor() {
            return floor;
            }

        void setFloor(int floor) {
            floor = floor;
            }

        bool isLight_status() {
            return light_status;
            }

        void setLight_status(bool light_status) {
            light_status = light_status;
            }

        double getCurrent_temp() {
            return current_temp;
            }

        void setCurrent_temp(double current_temp) {
            current_temp = current_temp;
            }

        double getMax_load_weight() {
            return max_load_weight;
        }

        void setMax_load_weight(double max_load_weight) {
            max_load_weight = max_load_weight;
            }

        int getMax_floor() {
            return max_floor;
            }

        void setMax_floor(int max_floor) {
            max_floor = max_floor;
            }

        double getMax_temp() {
            return max_temp;
            }

        void setMax_temp(double max_temp) {
            max_temp = max_temp;
            }
};