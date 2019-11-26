import serial
import time
from datetime import date
import csv
import os


class Measurements():
    self.sensor = "MPU6050"
    self.path = f"{datetime.date.today()}_LOG_{sensor}.csv"
    self.fieldsNames = ['AccX', 'AccY', 'AccZ', 'RotX', 'RotY', 'RotZ', 'dt']

    self.serial_port = 'COM4'
    self.baud_rate = 115200
    # path = "%s_LOG_%s.txt" % (str(datetime.now()), sensor)

    def startMeasurements():

        
        ser = serial.Serial()
        ser.baud_rate = self.baud_rate
        ser.port = self.serial_port

        ser.open()
        
        if  not os.path.exists(self.path):
            with open(path, mode='w', newline='') as csvFile:
                writer = csv.DictWriter(csvFile, fieldnames=fieldsNames)
                writer.writeheader()

        while True:
            line = ser.readline()
            line = line.decode("utf-8")  # ser.readline returns a binary, convert to string
            
            accX, accY, accZ, rotX, rotY, rotZ, dt = line.split(",")
            humidity = float(humidity)
            temperature = float(temperature)
            print(dt, accX, accY, accZ, rotX, rotY, rotZ)

            timeStamp = time.time()
            with open(path, mode='a', newline='') as csvFile:
                writer = csv.DictWriter(csvFile, fieldnames=fieldsNames)

                writer.writerow({fieldsNames[0]: accX*9.81, fieldsNames[1]: accY*9.81, fieldsNames[2]: accz*9.81, 
                    fieldsNames[3]: rotX, fieldsNames[4]: rotY, fieldsNames[5]: rotZ, fieldsNames[6]: dt})

m = Measurements()
m.startMeasurements()
