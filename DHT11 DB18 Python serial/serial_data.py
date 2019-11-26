import serial
import time
from datetime import date
import csv
import os
import numpy as np

sensor = "DH11_BMP_LM"
serial_port = 'COM7'
baud_rate = 9600
# path = "%s_LOG_%s.txt" % (str(datetime.now()), sensor)

path = f"{date.today()}_LOG_{sensor}.csv"
ser = serial.Serial()
ser.baud_rate = baud_rate
ser.port = serial_port

ser.open()
fieldsNames = ['Date', "Temperature BMP", "pressureBMP", "altitudeBMP", "Temperature DHT", "Humidity DHT", "Temperature LM"]
if  not os.path.exists(path):
    with open(path, mode='w', newline='') as csvFile:
        writer = csv.DictWriter(csvFile, fieldnames=fieldsNames)
        writer.writeheader()

data = np.zeros(7)
while True:
    line = ser.readline()
    line = line.decode("utf-8")  # ser.readline returns a binary, convert to string
    print(line)
    data[1::] = [float(value) for value in line.split(",")]
    # temperatureBMP, pressureBMP, altitudeBMP, temperatureDHT, humidityDHT, temperatureLM = line.split(",")
    # humidity = float(humidity)
    # temperature = float(temperature)

    timeStamp = time.time()
    data[0] = timeStamp
    with open(path, mode='a', newline='') as csvFile:
        writer = csv.DictWriter(csvFile, fieldnames=fieldsNames)

        # writer.writerow({fieldsNames[0]: timeStamp, fieldsNames[1]: temperature, fieldsNames[2]: humidity})
        writer.writerow({fieldsNames[i]: data[i] for i in range(len(data))})
