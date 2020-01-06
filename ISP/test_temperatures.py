import datetime
import sys
from os import path
import csv
import serial
import time
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from pandas.plotting import register_matplotlib_converters

register_matplotlib_converters()
# style.use('fivethirtyeight')

"""
Skrypt odczytujący dane z portu seryjnego
Domyślnie ustawienia to:
serial_port - COM4 (dla windows) - port szeregowy
baud_rate - 115200 buad - predkość przesyłu danych
Skrypt generuje plik csv z pomiarami z czujnikow
 """


class serialRead():
    def __init__(self, sensor='ISP', serial_port='COM4', dT='60000',
                 baud_rate='115200', sen_num=3, plotParams='n'):
        self.sensor = sensor
        self.plotParams = plotParams
        self.serial_port = serial_port
        self.baud_rate = baud_rate
        self.sen_num = sen_num
        self.dT = dT
        now = datetime.datetime.now()
        self.path = f'{now.strftime("%H-%M")}_LOGS_{self.sensor}_temp_test.csv'
        self.header = ['Time']
        if self.plotParams == 'y':
            self.fig, self.axs = fig, axs = plt.subplots(3, 1, constrained_layout=True)
            self.ylabel = ['Temp. *C', 'Cisn. hPa', 'Poz. nasw. lx.']
            self.axs[0].set_xlabel('Czas')
            plt.ion()
            plt.show()
        

        for i in range(self.sen_num):
            self.header.append(f'T_{i}')
            self.header.append(f'P_{i}')
            self.header.append(f'L_{i}')
        self.header.append('T_DHT11')
        self.header.append('T_LM35')
        print(
            f'Ustawiono: {self.baud_rate}, {self.serial_port}, {self.sensor}, {self.sen_num}')
        print(self.header)

    def plot_now(self):
        
        df = pd.read_csv(self.path)
        df['Time'] = pd.to_datetime(df['Time'], unit='s')
        
        for i, temp in zip(range(self.sen_num), ('T_', 'P_', 'L_')):
            self.axs[i].clear()
            for j in range(self.sen_num):
                col = temp+str(j)
                self.axs[i].plot(df[df.columns[0]], df[col], label=col)
            self.axs[i].set_ylabel(self.ylabel[i])
            self.axs[i].legend()
            self.axs[i].grid()

        self.axs[0].plot(df[df.columns[0]], df['T_DHT11'], label='T_DHT11')
        self.axs[0].plot(df[df.columns[0]], df['T_LM35'], label='T_LM35')
        self.axs[0].legend()
        plt.draw()
        plt.pause(0.001)

    def start(self):
        ser = serial.Serial()
        ser.baudrate = self.baud_rate
        ser.port = self.serial_port

        ser.open()
        
        dataBuffer = np.zeros(self.sen_num*3+3)
        # time_start = time.time()
        print('Serial status: ', ser.is_open)
        if not path.isfile(self.path):
            with open(self.path, mode='w', newline='') as csvFile:
                writer = csv.DictWriter(csvFile, fieldnames=self.header)
                writer.writeheader()
        # ser.write(b'start')
        print('Start')
        writedT = 0
        while True:
            
            line = ser.readline()
            line = line.decode('utf-8')

            dataBuffer[1::] = [float(val)
                               for val in line.split(",")]

            # dataBuffer[0] = time.time() - time_start
            dataBuffer[0] = time.time()
            # print(dataBuffer)
            
            if writedT == 0:
                ser.write(data=self.dT.encode())
                writedT = 1

            with open(self.path, mode='a', newline='') as csvFile:
                writer = csv.DictWriter(csvFile, fieldnames=self.header)

                writer.writerow({self.header[i]: dataBuffer[i]
                                 for i in range(len(dataBuffer))})
            if self.plotParams == 'y':
                self.plot_now()


if __name__ == "__main__":
    if sys.argv.__len__() == 2:
        com = sys.argv[1:]
        s = serialRead(serial_port=com)
    elif sys.argv.__len__() == 3:
        com, plot = sys.argv[1:]
        s = serialRead(serial_port=com, plotParams=plot)
    elif sys.argv.__len__() == 4:
        com, plot, dT = sys.argv[1:]
        s = serialRead(serial_port=com, plotParams=plot, dT=dT)
    else:
        s = serialRead(serial_port='COM3')
    
    print("Odczyt danych z portu szeregowego, włącz skrypt do szukania adresów bądz zrestartuj Arduino Nano z wgranym skryptem")
    s.start()
