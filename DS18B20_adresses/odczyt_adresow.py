import serial
import time
import datetime
import csv
import os


class serialRead():
    def __init__(self, sensor='DS18B20', serial_port='COM3', baud_rate='9600'):
        self.sensor = sensor
        self.serial_port = serial_port
        self.baud_rate = baud_rate
        self.path = f'{datetime.date.today()}_ADRESES_{self.sensor}.txt'
        self.header = f'Adresy czujnikow {self.sensor}\nData: {datetime.datetime.now()}\n---------------------------------------------- \n'

    def start(self):
        ser = serial.Serial()
        ser.baud_rate = self.baud_rate
        ser.port = self.serial_port

        ser.open()

        if not os.path.exists(self.path):
            with open(self.path, mode='w', newline='') as file:
                file.write(self.header)
        
        while True:
            line = ser.readline()
            line = line.decode('utf-8')

            with open(self.path, mode='a', newline='') as file:
                file.write(line)


if __name__ == "__main__":
    s = serialRead()
    s.start()
    