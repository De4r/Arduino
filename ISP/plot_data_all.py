import matplotlib.pyplot as plt
import pandas as pd
import datetime

filename = 'Test1.csv'
filename = 'Test2.csv'
filename = '02-01-2020_LOGS_ISP.csv'
filename = '03-01-2020_LOGS_ISP.csv'
filename = '04-01-2020_LOGS_ISP.csv'
filename = '05-01-2020_LOGS_ISP.csv'
filename = 'Test1_KOR.csv'
filename = 'Test2_KOR.csv'
filename = '02-01-2020_LOGS_ISP_KOR.csv'
filename = '03-01-2020_LOGS_ISP_KOR.csv'
filename = '04-01-2020_LOGS_ISP_KOR.csv'
filename = '05-01-2020_LOGS_ISP_KOR.csv'

sen_num=3
df = pd.read_csv(filename)

# df['T_0'] = round(df['T_0'] - 1.03, 2)
# df['T_1'] = round(df['T_1'] - 1.715, 2)
# df['T_2'] = round(df['T_2'] - 1.325, 2)
# # df['P_1'] = round(df['P_1'] + 1.1, 2)

# filename1 = '05-01-2020_LOGS_ISP_KOR.csv'
# df.to_csv(filename1, index=False)

# df = pd.read_csv(filename1)

# df['Time'] = pd.Timestamp(int(df['Time']), unit='s', tz='Europe/Warsaw')
df['Time'] = pd.to_datetime(df['Time'], unit='s')
df['Time']= df['Time'].dt.tz_localize("GMT").dt.tz_convert('Europe/Warsaw')
print(df.head())


fig, axs = fig, axs = plt.subplots(3, 1, constrained_layout=True)
ylabel = ['Temp. *C', 'Cisn. hPa', 'Poz. nasw. lx.']
axs[0].set_xlabel('Czas')

for i, temp in zip(range(sen_num), ('T_', 'P_', 'L_')):
    axs[i].clear()
    for j in range(sen_num):
        col = temp+str(j)
        axs[i].plot(df[df.columns[0]], df[col], label=col)
        axs[i].set_ylabel(ylabel[i])
        axs[i].ticklabel_format(axis='y', style='', useOffset=False)
        axs[i].legend()
        axs[i].grid()
plt.setp(axs[0].get_xticklabels(), visible=False)
plt.setp(axs[1].get_xticklabels(), visible=False)


plt.show()

# fig2 = plt.figure()
# i = df.loc[df['Time'] > 1250].index.values[0]
# for col in df.columns[1::]:
#     ax = plt.plot(df[df.columns[0]][i:], df[col][i:], label=col)

# plt.grid()
# plt.title('Ustalony przebieg temperatury dla pomiaru 1')
# plt.xlabel('Czas [s]')
# plt.ylabel('Temperatura [st. C]')
# plt.legend()
# plt.show(block=False)



# # usredniania

# df_mean = df.copy(deep = True)
# df_mean[df_mean.columns[1:17]] = df_mean[df_mean.columns[1:17]].rolling(window=25, center=True, min_periods=1).mean()
# df_mean[df_mean.columns[-1]] = df_mean[df_mean.columns[-1]].rolling(window=50, center=True, min_periods=1).mean()
# # df_mean.loc[df_mean['Time'] > 50, df_mean.columns[-1]] = df_mean.loc[df_mean['Time'] > 50, df_mean.columns[-1]].rolling(window=50, center=True, min_periods=1).mean()
# fig3 = plt.figure()

# for col in df_mean.columns[1::]:
#     ax = plt.plot(df_mean[df_mean.columns[0]], df_mean[col], label=col)

# plt.grid()
# plt.title('Przebieg czasowy tempratury w punktach pomiarowych dla pomiaru 1 po wygladzeniu przebiegow')
# plt.xlabel('Czas [s]')
# plt.ylabel('Temperatura [st. C]')
# plt.legend()
# plt.show(block=False)


# fig4 = plt.figure()

# cols = ['T_6', 'T_c']

# for col in cols:
#     # temp T_c i T_6
#     ax1 = plt.plot(df_mean[df_mean.columns[0]], df_mean[col], label=col)

# # obliczenie dT z przebiegu plus wykres
# df_mean['dT'] = df_mean[cols[0]] - df_mean[cols[-1]]
# # df_mean.loc[df_mean['Time'] > 50, df_mean.columns[-1]] = df_mean.loc[df_mean['Time'] > 50, df_mean.columns[-1]].rolling(window=100, center=True, min_periods=1).mean()
# ax1 = plt.plot(df_mean[df_mean.columns[0]], df_mean[df_mean.columns[-1]], label=df_mean.columns[-1])

# plt.title(f'Przebieg czasowy tempratur modulu peltiera dla pomiaru 1')
# plt.xlabel('Czas [s]')
# plt.ylabel('Temperatura [st. C]')
# plt.legend()
# plt.grid()
# plt.show()

# i = df.loc[df_mean['Time'] > 400].index.values[0]
# print('Średnia rożnica temperatury modulu dla ustalonej pracy: ', round(df_mean[df_mean.columns[-1]][i:].mean(), 2))
# print('Średnia temperatura otoczenia podczas pomiaru: ', round(df[df.columns[-2]].mean(), 2))
# # print(df.loc[0, df.columns[1:16]].to_numpy())
# print('Średnia temperatura plytki w chwilis startu podczas pomiaru: ', round(df.loc[0, df.columns[1:16]].mean(), 2))
