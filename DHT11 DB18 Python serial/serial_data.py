import serial
import time
from datetime import date
import csv
import os

sensor = "DH11"
serial_port = 'COM3'
baud_rate = 9600
# path = "%s_LOG_%s.txt" % (str(datetime.now()), sensor)

path = f"{date.today()}_LOG_{sensor}.csv"
ser = serial.Serial()
ser.baud_rate = baud_rate
ser.port = serial_port

ser.open()
fieldsNames = ['Date', "Temperature", "Humidity"]
if  not os.path.exists(path):
    with open(path, mode='w', newline='') as csvFile:
        writer = csv.DictWriter(csvFile, fieldnames=fieldsNames)
        writer.writeheader()

while True:
    line = ser.readline()
    line = line.decode("utf-8")  # ser.readline returns a binary, convert to string
    print(line)
    humidity, temperature = line.split(",")
    humidity = float(humidity)
    temperature = float(temperature)

    timeStamp = time.time()
    with open(path, mode='a', newline='') as csvFile:
        writer = csv.DictWriter(csvFile, fieldnames=fieldsNames)

        writer.writerow({fieldsNames[0]: timeStamp, fieldsNames[1]: temperature, fieldsNames[2]: humidity})
