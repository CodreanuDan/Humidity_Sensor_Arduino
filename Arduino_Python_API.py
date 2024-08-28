import serial
import time

# Open the serial port
arduino = serial.Serial(port='COM11',   baudrate=9600, timeout=.1)  
class Arduino_API():

    def write_read():

        # invalid_value = "[##] Invalid value !!!"
        # if   arduino != None:

        try:
            while True:

                #//////////////////////////////////////////////////////////////////////////////#
                #//////////////////>> New_version-capacitance + DHT 11 RH% <<//////////////////#
                #//////////////////////////////////////////////////////////////////////////////#

            	# Read raw data from the serial port
                raw_data = arduino.readline()
                if not raw_data:
                    continue  
                decoded_data = raw_data.decode('utf-8').strip()    
                time.sleep(0.5)
                data_list = decoded_data.split(" ")
                try:
                    int_list = [int(item) for item in data_list]
                    if len(int_list) == 2:
                        return int_list
                except Exception as e:
                    print("[###] Exception in arduino_api[write_read(<!> INVALID LENGTH - DATA FROM SERIAL <!>)]", e) 
        except Exception as e:
            print("[##] Exception in arduino_api(write_read):", e) 
            return []

    

              
                