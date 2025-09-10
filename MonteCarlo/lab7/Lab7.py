import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Funkcje
def algortyn_gillespie(bazowy_df= pd.DataFrame(
        {'X1': [120], 'X2': [80], 'X3': [1], 't': [0]}),
        Pmax=1, tmax=200, k1=1, k2=1, k3=0.001, k4=0.01, N=50
        ):

    kolekcja = [bazowy_df.copy() for i in range(Pmax)]
    for p in range(Pmax):
        t = 0
        while t < tmax:
            x1 = kolekcja[p]['X1'].iloc[-1]
            x2 = kolekcja[p]['X2'].iloc[-1]
            x3 = kolekcja[p]['X3'].iloc[-1]

            G1 = k1
            G2 = k2
            G3 = k3*x1*x2
            G4 = k4*x3
            Gmax = G1+G2+G3+G4

            U1, U2 = np.random.uniform(0, 1, 2)
            dt = -(1)/(Gmax)*np.log(U1)

            if U2 <= G1/Gmax:
                #m=1
                x1 += 1
            elif U2 <= (G1+G2)/Gmax:
                #m=2
                x2 += 1
            elif U2 <= (G1+G2+G3)/Gmax:
                #m=3
                x1 -= 1; x2 -= 1; x3 += 1
            else:
                #m=4
                x3 -= 1

            nowe_dane = pd.DataFrame({'X1': [x1], 'X2': [x2], 'X3': [x3], 't': [t]})
            kolekcja[p] = pd.concat([kolekcja[p], nowe_dane], ignore_index=True)
            
            # Koniec pętli while
            t += dt
    return kolekcja

def algortyn_gillespie_z_krokiem(bazowy_df= pd.DataFrame(
        {'X1': [120], 'X2': [80], 'X3': [1]}),
        Pmax=1, tmax=200, k1=1, k2=1, k3=0.001, k4=0.01, N=50
        ):

    kolekcja = [bazowy_df.copy() for i in range(Pmax)]
    for p in range(Pmax):
        t = 0
        while t < tmax:
            x1 = kolekcja[p]['X1'].iloc[-1]
            x2 = kolekcja[p]['X2'].iloc[-1]
            x3 = kolekcja[p]['X3'].iloc[-1]

            G1 = k1
            G2 = k2
            G3 = k3*x1*x2
            G4 = k4*x3
            Gmax = G1+G2+G3+G4

            U1, U2 = np.random.uniform(0, 1, 2)
            dt = -(1)/(Gmax)*np.log(U1)

            if U2 <= G1/Gmax:
                #m=1
                x1 += 1
            elif U2 <= (G1+G2)/Gmax:
                #m=2
                x2 += 1
            elif U2 <= (G1+G2+G3)/Gmax:
                #m=3
                x1 -= 1; x2 -= 1; x3 += 1
            else:
                #m=4
                x3 -= 1

            l = int(t / tmax * N)
            nowe_dane = pd.DataFrame({'X1': [x1], 'X2': [x2], 'X3': [x3]}, index=[l])
            kolekcja[p] = pd.concat([kolekcja[p], nowe_dane])
            
            # Koniec pętli while
            t += dt
        kolekcja[p] = kolekcja[p].loc[~kolekcja[p].index.duplicated(keep='last')]
    return kolekcja

# Parametry 
tmax=200; k1=1; k2=1; k3=0.001; k4=0.01; N=50

# Dla Pmax = 1

# Pmax=1
# kolekcja = algortyn_gillespie(Pmax=Pmax, tmax=tmax, k1=k1, k2=k2, k3=k3, k4=k4, N=N)
# df = kolekcja[0]

# plt.figure(figsize=(10, 6))
# plt.plot(df['t'], df['X1'], label=f'X1', linestyle='-', color='r')
# plt.plot(df['t'], df['X2'], label=f'X2', linestyle='-', color='b')
# plt.plot(df['t'], df['X3'], label=f'X3', linestyle='-', color='g')
# plt.xlabel('t')
# plt.ylabel('X1, X2, X3')
# plt.title('Przebieg w czasie Pmax={Pmax}, k1=k2={k1}, k3={k3}, k4={k4}'.format(Pmax=Pmax, k1=k1, k3=k3, k4=k4))
# plt.legend()
# plt.grid(True)
# plt.savefig('Przebieg_Pmax=1.png')
# plt.clf()
# plt.close()

# Dla Pmax = 5

# Pmax=5
# kolekcja = algortyn_gillespie(Pmax=Pmax, tmax=tmax, k1=k1, k2=k2, k3=k3, k4=k4, N=N)
# handles = []
# labels = []

# plt.figure(figsize=(10, 6))
# for i in range(5):
#     df = kolekcja[i]
#     line1, = plt.plot(df['t'], df['X1'], label=f'X1', linestyle='-', color='r')
#     line2, = plt.plot(df['t'], df['X2'], label=f'X2', linestyle='-', color='b')
#     line3, = plt.plot(df['t'], df['X3'], label=f'X3', linestyle='-', color='g')
#     if i == 0:
#         handles.extend([line1, line2, line3])
#         labels.extend([f'X1', f'X2', f'X3'])
# plt.xlabel('t')
# plt.ylabel('X1, X2, X3')
# plt.title('Przebieg w czasie Pmax={Pmax}, k1=k2={k1}, k3={k3}, k4={k4}'.format(Pmax=Pmax, k1=k1, k3=k3, k4=k4))
# plt.legend(handles=handles, labels=labels)
# plt.grid(True)
# plt.savefig('Przebieg_Pmax=5.png')
# plt.clf()
# plt.close()

# Dla Pmax = 100

Pmax = 100
kolekcja = algortyn_gillespie_z_krokiem(Pmax=Pmax, tmax=tmax, k1=k1, k2=k2, k3=k3, k4=k4, N=N)

all_data = []
for df in kolekcja:
    df_sorted = df.reset_index(drop=True)
    all_data.append(df_sorted[['X1', 'X2', 'X3']].values)

df['t'] = df.index

data_array = np.array(all_data)  
# shape: (100, T, 3)
mean_over_time = np.mean(data_array, axis=0)  
# shape: (T, 3)
std_over_time = np.std(data_array, axis=0)    
# shape: (T, 3)

mean_df = pd.DataFrame(mean_over_time, columns=['X1_mean', 'X2_mean', 'X3_mean'])
std_df = pd.DataFrame(std_over_time, columns=['X1_mean', 'X2_mean', 'X3_std'])

mean_df['t'] = df['t']
std_df['t'] = df['t']

plt.figure(figsize=(10, 6))

plt.plot(mean_df['t'], mean_df['X3_mean'], label='Średnia X3')
plt.fill_between(mean_df['t'],
                 mean_df['X3_mean'] - std_df['X3_std'],
                 mean_df['X3_mean'] + std_df['X3_std'],
                 color='blue', alpha=0.2, label='± std')

plt.xlabel('t')
plt.ylabel('X1')
plt.title('Przebieg w czasie Pmax={Pmax}, k1=k2={k1}, k3={k3}, k4={k4}'.format(Pmax=Pmax, k1=k1, k3=k3, k4=k4))
plt.legend()
plt.grid(True)
plt.savefig('Przebieg_Pmax=100.png')
plt.clf()
plt.close()
