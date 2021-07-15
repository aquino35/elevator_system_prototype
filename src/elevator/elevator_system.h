/*
 * TODO : DOCUMENT
 * 
 * 
 */

class System {

    protected:

        bool door_status;
        double load_weight;
        int floor;
        bool light_status;
        double current_temp; 
        double max_load_weight;
        int max_floor;
        double max_temp;

    public:

        virtual bool isDoor_status() = 0;

        virtual void setDoor_status(bool door_status) = 0;

        virtual double getLoad_weight() = 0;

        virtual void setLoad_weight(double load_weight) = 0;

        virtual int getFloor() = 0;

        virtual void setFloor(int floor) = 0;

        virtual bool isLight_status() = 0;

        virtual void setLight_status(bool light_status) = 0;

        virtual double getCurrent_temp() = 0;

        virtual void setCurrent_temp(double current_temp) = 0;

        virtual double getMax_load_weight() = 0;

        virtual void setMax_load_weight(double max_load_weight) = 0;

        virtual int getMax_floor() = 0;

        virtual void setMax_floor(int max_floor) = 0;

        virtual double getMax_temp() = 0;
        
        virtual void setMax_temp(double max_temp) = 0;

};