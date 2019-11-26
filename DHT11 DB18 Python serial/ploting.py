import datetime
import matplotlib.pyplot as plt
import csv
import pandas
from pandas.plotting import register_matplotlib_converters
register_matplotlib_converters()


sensor = "DH11_BMP_LM"
path = f"{datetime.date.today()}_LOG_{sensor}.csv"
fieldsNames = ['Date', 'Temperature BMP', 'pressureBMP', 'altitudeBMP', 'Temperature DHT', 'Humidity DHT', 'Temperature LM']

df = pandas.read_csv(path)
print(df.head())

df['Date'] = pandas.to_datetime(df['Date'], unit='s')

print(df.head())
fig, axs = plt.subplots(ncols=3, nrows=2)
gs = axs[0,2].get_gridspec()
for ax in axs[0, :]:
    ax.remove()
axtemp = fig.add_subplot(gs[0, :])

for i in (1, 4, 6):
    axtemp.plot(df[fieldsNames[0]], df[fieldsNames[i]], label=fieldsNames[i])
axtemp.legend()
axtemp.grid()
for i,j in zip([0, 1, 2], [2, 3 ,5]):
    axs[1, i].plot(df[fieldsNames[0]], df[fieldsNames[j]], label=fieldsNames[j])
    axs[1, i].legend()
    axs[1, i].grid()


plt.show()