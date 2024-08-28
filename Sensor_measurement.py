import time
import datetime
import json
import csv
from Arduino_Python_API import Arduino_API 


class Sensor_measurement():

    def calculate_variable_constants(cap_value):

        try:
            if float(cap_value) <= 100:
                var_const = 1.5
                ter29 = -29.129 + 18
            elif float(cap_value) <= 80:
                var_const = 0.5
                ter29 = -29.129 + 35
            elif float(cap_value) <= 70:
                var_const = 0.5
                ter29 = -29.129 + 55 
            elif float(cap_value) <= 60:
                var_const = 0.5
                ter29 = -29.129 + 15
            elif float(cap_value) <= 49:
                var_const = 0.5
                ter29 = -29.129 + 15
            elif float(cap_value) <= 20:
                var_const = 0.5
                ter29 = -29.129 
            else:
                var_const = 1.75
                ter29 = -29.129
            return var_const,ter29
        except Exception as e:
            print("[###] Exception in sensor_measurement(calculate_variable_constants):", e)

    def calculate_relative_humidity(cap_value, ter29, var_const):

        #  FORMULA CALCUL UMIDITATE =1.418RH+29.139 (https://www.matec-conferences.org/articles/matecconf/pdf/2016/22/matecconf_icfst2016_01011.pdf)
        # <OK!>C=2.760*RH+29.139 adaptat pentru capacitor DHT 11(sample rate: 100ms)
        # <OK!>, formula initiala: C = 1.418*RH + 29.129(exemplu)
        # <OK!>C=5.072*RH+29.139 asaptat pt samplerate (150ms)

        try:
            if cap_value != '':
                relative_humidity = float( (float(cap_value-30) + ter29) // var_const)
                if   relative_humidity >= 100.0:
                        relative_humidity_show = 100.0
                elif relative_humidity <= 65:
                        relative_humidity_show = relative_humidity + 25
                elif relative_humidity <= 40:
                        relative_humidity_show = relative_humidity + 31
                elif relative_humidity <= 30 and cap_value <35:
                        relative_humidity_show = relative_humidity + 54
                elif relative_humidity <= 30 and cap_value <48:
                        relative_humidity_show = relative_humidity + 54
                elif relative_humidity <= 0:
                    relative_humidity_show = relative_humidity + 62
                else:
                    relative_humidity_show = relative_humidity + 50
            else:
                pass
            return relative_humidity_show
        except Exception as e:
            print("[###] Exception in sensor_measurement(calculate_relative_humidity):", e)
    
    def json_dump(cap_value,i,relative_humidity_show,dht_value):

        dt_time = datetime.datetime.now().strftime("%d.%m.%Y-%H:%M:%S")

        try:
            if cap_value == "" or cap_value == "[##] Invalid value !!!":
                    pass   
            else:
                # data save in JSON for site visualisation
                json_data = {
                                "date_time":str(dt_time),
                                "iteration":str(i),
                                "cap_value":str(cap_value),
                                "rh":str(relative_humidity_show),
                                "dht_rh":str(dht_value),
                            }
                    
                with open('temp_data.json', 'w') as json_file:
                        json.dump(json_data,json_file)
        except Exception as e:
            print("[###] Exception in sensor_measurement(json_dump):", e)

    def csv_dump(i,relative_humidity_show):
         try:

            dt_time = datetime.datetime.now().strftime("%d.%m.%Y-%H:%M:%S")

            header = ['Date&Time', 'Cap_VAL', 'RH', 'DHT_RH']
            # row = [dt_time,cap_value,relative_humidity_show,dht_value]
            row = [i,relative_humidity_show]

            with open('temp_data.csv', 'a' ,encoding='UTF8', newline='') as csv_file:
                writer = csv.writer(csv_file)
                # write the header
                # writer.writerow(header)
                # write the data
                writer.writerow(row)
         except Exception as e:
              print("[###] Exception in sensor_measurement(csv_dump):", e)

    def print_data(cap_value,relative_humidity_show,dht_value):

        dt_time = datetime.datetime.now().strftime("%d.%m.%Y-%H:%M:%S")
        try:
            print(f"--> {dt_time} : Capacitor value : {cap_value} nF and [[RH: {relative_humidity_show} % ]]- DHT 11 RH {dht_value} %.")
        except Exception as e:
            print("[###] Exception in sensor_measurement(print_data):", e)

    def sensor_measurement():

        dt_time = datetime.datetime.now().strftime("%d.%m.%Y-%H:%M:%S")

        try:
            i= 0
            while True:
                serial_data= Arduino_API.write_read()
                i += 1
                nr_masurari = i
                cap_value = serial_data[1]
                dht_value = serial_data[0]

                var_const, ter29 = Sensor_measurement.calculate_variable_constants(cap_value)
                relative_humidity_show = Sensor_measurement.calculate_relative_humidity(cap_value, ter29, var_const)
                
                if cap_value == "" or cap_value == "[##] Invalid value !!!":
                    pass   
                else:
                    #data handling
                    Sensor_measurement.json_dump(cap_value,i,relative_humidity_show,dht_value)
                    Sensor_measurement.csv_dump(i,relative_humidity_show)
                    #display data
                    Sensor_measurement.print_data(cap_value,relative_humidity_show,dht_value)
                    
        except Exception as e:
            print("[##] Exception in sensor_measurement(sensor_measurement):", e)