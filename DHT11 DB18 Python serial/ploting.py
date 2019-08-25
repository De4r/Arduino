import datetime
import matplotlib.pyplot as plt
import csv
import pandas


sensor = "DH11"
path = f"{datetime.date.today()}_LOG_{sensor}.csv"
fieldsNames = ['Date', "Temperature", "Humidity"]

df = pandas.read_csv(path)
print(df.head())

df['Date'] = pandas.to_datetime(df['Date'], unit='s')

print(df.head())

plt.plot(df['Date'], df['Temperature'])
plt.plot(df['Date'], df['Humidity'])
plt.show()