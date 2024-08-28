import time
import serial
import threading
import tkinter as tk
from tkinter import ttk
from Arduino_Python_API import Arduino_API 
from Sensor_measurement import Sensor_measurement

def measure_report():

    try:
            time.sleep(0.5)
            print("\n")
            print("\n")
            print("//////////////////////////////////////////////////////////////")
            print("//////////////////__Sensor_Measurement_v1.0_//////////////////") 
            print("//////////////////////////////////////////////////////////////\n")
            print("\n") 
            time.sleep(0.5)
            print(f"[#] Starting reciving data from serial port \n")
            time.sleep(0.5)  
            Sensor_measurement.sensor_measurement()
    except Exception as e:
        print("[##] Exception in measure_report:", e)

             
if __name__ == '__main__':

    t1 = threading.Thread(target=measure_report)
    
    try:
        t1.start()
    except KeyboardInterrupt:
        print("\n[##] KeyboardInterrupt: Exiting the program.")
    except Exception as e:
        print("[##] Exception in main:", e)
    
