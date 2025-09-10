import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os


def potencjal_brennera_opt(
    bazowy_df=pd.DataFrame({'x': [0, 1, 2, 3], 'y': [0, 1, 2, 3], 'z': [0, 1, 2, 3]}),
    R0=1.315, R1=1.70, R2=2.00, De=6.325, S=1.29,
    lambd=1.5, sigma=0.80469, a0=0.011304, c0=19, d0=2.5):

    coords = bazowy_df[['x', 'y', 'z']].values
    N = coords.shape[0]

    # --- TABLICA B ---
    B = np.zeros((N, N))
    for i in range(N):
        pi = coords[i]
        for j in range(N):
            if j == i:
                continue
            pj = coords[j]
            r_ij = pj - pi
            norm_rij = np.linalg.norm(r_ij)

            zeta = 0
            for k in range(N):
                if k == i or k == j:
                    continue
                pk = coords[k]
                r_ik = pk - pi
                norm_rik = np.linalg.norm(r_ik)

                if norm_rik <= R2:
                    # Funkcja odcięcia
                    if norm_rik <= R1:
                        fcut = 1
                    else:
                        fcut = 0.5 * (1 + np.cos((norm_rik - R1) / (R2 - R1) * np.pi))
                    # Obliczenie g
                    cos_theta = np.clip(np.dot(r_ij, r_ik) / (norm_rij * norm_rik), -1.0, 1.0)

                    g = a0 * (1 + c0**2 / d0**2 - c0**2 / (d0**2 + (1 + cos_theta)**2))
                    zeta += fcut * g

            B[i, j] = (1 + zeta) ** (-sigma)


    # --- TABLICA V ---
    V = np.zeros(N)
    for i in range(N):
        pi = coords[i]
        Vi = 0
        for j in range(N):
            if j == i:
                continue
            pj = coords[j]
            r = np.linalg.norm(pi - pj)

            if r <= R2:
                # Funkcja odcięcia
                if r <= R1:
                    fcut = 1
                else:
                    fcut = 0.5 * (1 + np.cos((r - R1) / (R2 - R1) * np.pi))

                # Składniki potencjału
                VR = (De / (S - 1)) * np.exp(-np.sqrt(2 * S) * lambd * (r - R0))
                VA = ((De * S) / (S - 1)) * np.exp(-np.sqrt(2 / S) * lambd * (r - R0))
                B_avg = (B[i, j] + B[j, i]) / 2

                Vi += fcut * (VR - B_avg * VA)

        V[i] = Vi

    V_tot = np.sum(V) / 2
    return V_tot, V, B


def delta_diraca (i: int, j: int):
    if i == j:
        return 1
    else:
        return 0

# def korelacja_par (bazowy_df= pd.DataFrame(
#         {'x': [0, 1, 2, 3], 'y': [0, 1, 2, 3], 'z': [0, 1, 2, 3]}),
#         beta_min = 1.0, beta_max = 100, p = 2, it_max = 105, wr = 10**(-4), w_phi = 0.05, w_theta = 0.05, w_all = 10**(-4),
#         M = 100
#     ):
#     N = bazowy_df.shape[0]
#     r = bazowy_df.apply(lambda x: np.linalg.norm(x), axis='columns').values
    
#     # Część właściwa
#     r_avg = np.mean(r)
#     r_max = 2.5 * r_avg
#     dr = r_max / M
#     omega = 4*np.pi*(r_avg**2)
    
#     # Algorytm
#     pcf1 = np.zeros(M)
#     for i in range(N):
#         for j in range(i+1, N):
#             pi = bazowy_df.iloc[i]
#             pj = bazowy_df.iloc[j]
#             ## Tutaj wg skryptu jest pj-pi
#             r = np.linalg.norm(pi)
#             m = int(r/dr)
#             if m < M:
#                 pcf1[m] += ( 2*omega ) / ( (N**2)*2*np.pi*r*dr )

#     # Z definicji
#     pcf2 = np.zeros(M)
#     for m in range(M):
#         r_m = (m+1/2)*dr
#         k = int(r_m/dr)
#         d_mk = 0
#         for i in range(N):
#             for j in range(i+1, N):
#                 d_mk += delta_diraca(m, k)
#         pcf2[m] = 2*omega / (N**2) * d_mk / (2*np.pi*r_m*dr)

    # r_values = np.linspace(0, r_max, M)
    # plt.plot(r_values, pcf1)
    # plt.xlabel("Odległość r")
    # plt.ylabel("PCF")
    # plt.title("Funkcja korelacji par")
    # plt.savefig('PCF1.png')
    # plt.clf()
    # plt.close()

    # plt.plot(r_values, pcf2)
    # plt.xlabel("Odległość r")
    # plt.ylabel("PCF")
    # plt.title("Funkcja korelacji par")
    # plt.savefig('PCF2.png')
    # plt.clf()
    # plt.close()
    # return pcf1, pcf2, r_values

def korelacja_par(bazowy_df, M=100):
    N = bazowy_df.shape[0]
    positions = bazowy_df[['x', 'y', 'z']].values

    # r_i względem środka układu
    r_i = np.linalg.norm(positions, axis=1)
    r_avg = np.mean(r_i)
    r_max = 2.5 * r_avg
    dr = r_max / M
    omega = 4 * np.pi * (r_avg ** 2)

    # Inicjalizacja PCF
    pcf = np.zeros(M)

    for i in range(N):
        for j in range(i + 1, N):
            rij = np.linalg.norm(positions[i] - positions[j])
            m = int(np.floor(rij / dr))
            if m < M:
                r_m = (m + 0.5) * dr
                pcf[m] += (2 * omega) / (N**2 * 2 * np.pi * r_m * dr)

    # Rysowanie
    r_bins = np.array([(m + 0.5) * dr for m in range(M)])
    plt.plot(r_bins, pcf)
    plt.xlabel("Odległość r")
    plt.ylabel("Funkcja korelacji par (PCF)")
    plt.title("PCF – Histogram")
    plt.grid(True)
    plt.savefig("pcf_histogram.png")
    plt.close()

    return pcf, r_bins


# def symulowane_wyzarzanie (bazowy_df= pd.DataFrame(
#         {'x': [0, 1, 2, 3], 'y': [0, 1, 2, 3], 'z': [0, 1, 2, 3]}),
#         R0=1.315, R1=1.70, R2=2.00, De=6.325, S=1.29, lambd=1.5, sigma=0.80469, a0=0.011304, c0=19, d0=2.5,
#         beta_min = 1.0, beta_max = 100, p = 2, it_max = 105, w_r = 10**(-4), w_phi = 0.05, w_theta = 0.05, w_all = 10**(-4), M = 100):
    
#     N = bazowy_df.shape[0]
#     bazowy_df['r'] = bazowy_df.apply(lambda x: np.linalg.norm(x), axis='columns').values
#     # kąt zenitalny
#     bazowy_df['theta'] = np.arccos(bazowy_df['z'] / bazowy_df['r'])    
#     # kąt azymutalny          
#     bazowy_df['phi'] = np.arctan2(bazowy_df['y'], bazowy_df['x']) 
#     df = bazowy_df
#     df_new = bazowy_df.copy()

#     # Losowanie wartości losowych
#     U = np.random.uniform(0, 1, (N, 4))  # N x 4 macierz

#     # Oblicz zmiany (dr, dphi, dtheta)
#     dr = (2 * U[:, 0] - 1) * w_r * df['r']
#     dphi = (2 * U[:, 1] - 1) * w_phi * df['phi'] + df['phi']
#     dtheta = (2 * U[:, 2] - 1) * w_theta * df['theta'] + df['theta']

#     # Korekty kątów do zakresu [0, 2π]
#     dphi = np.mod(dphi, 2 * np.pi)
#     dtheta = np.mod(dtheta, 2 * np.pi)

#     # Aktualizacja współrzędnych sferycznych
#     df_new['r'] += dr
#     df_new['phi'] = dphi
#     df_new['theta'] = dtheta

#     # Aktualizacja współrzędnych kartezjańskich
#     df_new['x'] = df_new['r'] * np.sin(df_new['theta']) * np.cos(df_new['phi'])
#     df_new['y'] = df_new['r'] * np.sin(df_new['theta']) * np.sin(df_new['phi'])
#     df_new['z'] = df_new['r'] * np.cos(df_new['theta'])
    
#     _, V_old, _ = potencjal_brennera_opt(bazowy_df=df)
#     _, V_new, _ = potencjal_brennera_opt(bazowy_df=df_new)

#     beta = beta_min
#     p_acc = min(e**(-beta(V_new-V_old)), 1)
#     # Tablica akceptowanych stanów
#     acc = p_acc >= U[:, 4]
    
#     return df

def symulowane_wyzarzanie_zapisywanie(
    bazowy_df,
    R0=1.315, R1=1.70, R2=2.00, De=6.325, S=1.29,
    lambd=1.5, sigma=0.80469, a0=0.011304, c0=19, d0=2.5,
    beta_min=1.0, beta_max=100, it_max=100,
    w_r=1e-4, w_phi=0.05, w_theta=0.05, w_all=1e-4,
    zapis_sciezka='wyniki.csv',
    zapis_koordynatow='koordynaty_iteracje.csv'):

    df = bazowy_df.copy()
    N = df.shape[0]

    df['r'] = np.linalg.norm(df[['x', 'y', 'z']].values, axis=1)
    df['theta'] = np.arccos(df['z'] / df['r'])
    df['phi'] = np.arctan2(df['y'], df['x'])

    V_tot_old, V_old, _ = potencjal_brennera_opt(bazowy_df=df)

    historia_energii = []

    with open(zapis_koordynatow, 'w') as f:
        f.write("iteracja,atom,x,y,z\n")  # nagłówek

    for it in range(it_max):
        beta = beta_min + ((it / it_max) ** 2) * (beta_max - beta_min)

        for i in range(N):
            df_new = df.copy(deep=True)
            U1, U2, U3 = np.random.uniform(0, 1, 3)

            dr = (2 * U1 - 1) * w_r * df.loc[i, 'r']
            dphi = (2 * U2 - 1) * w_phi * df.loc[i, 'phi']
            dtheta = (2 * U3 - 1) * w_theta * df.loc[i, 'theta']

            r_new = df.loc[i, 'r'] + dr
            phi_new = np.mod(df.loc[i, 'phi'] + dphi, 2 * np.pi)
            theta_new = np.mod(df.loc[i, 'theta'] + dtheta, 2 * np.pi)

            x_new = r_new * np.sin(theta_new) * np.cos(phi_new)
            y_new = r_new * np.sin(theta_new) * np.sin(phi_new)
            z_new = r_new * np.cos(theta_new)

            df_new.loc[i, ['r', 'phi', 'theta', 'x', 'y', 'z']] = [r_new, phi_new, theta_new, x_new, y_new, z_new]

            _, V_test, _ = potencjal_brennera_opt(bazowy_df=df_new)
            dV = V_test[i] - V_old[i]
            p_accept = np.exp(-beta * dV) if dV > 0 else 1.0

            #print(p_accept)
            if np.random.rand() < p_accept:
                #print('zaakceptowano')
                df.loc[i, ['r', 'phi', 'theta', 'x', 'y', 'z']] = df_new.loc[i, ['r', 'phi', 'theta', 'x', 'y', 'z']]
                V_old[i] = V_test[i]

        # Globalna skala promienia
        df_global = df.copy(deep=True)
        U_global = np.random.uniform(0, 1)
        scale = 1 + w_all * (2 * U_global - 1)

        df_global['r'] = df['r'] * scale
        df_global['x'] = df_global['r'] * np.sin(df['theta']) * np.cos(df['phi'])
        df_global['y'] = df_global['r'] * np.sin(df['theta']) * np.sin(df['phi'])
        df_global['z'] = df_global['r'] * np.cos(df['theta'])

        V_tot_new, _, _ = potencjal_brennera_opt(bazowy_df=df_global)
        dV_tot = V_tot_new - V_tot_old
        p_global = np.exp(-beta * dV_tot) if dV_tot > 0 else 1.0

        if np.random.rand() < p_global:
            df = df_global
            V_old = np.array([V_tot_new / N] * N)
            V_tot_old = V_tot_new

        historia_energii.append(V_tot_old)

        # Zapis współrzędnych
        with open(zapis_koordynatow, 'a') as f:
            for i in range(N):
                f.write(f"{it},{i},{df.loc[i, 'x']},{df.loc[i, 'y']},{df.loc[i, 'z']}\n")

    # Zapis energii
    pd.DataFrame({'energia': historia_energii}).to_csv(zapis_sciezka, index_label='iteracja')

    return df, historia_energii

def rysuj_energie(historia_energii):
    import matplotlib.pyplot as plt

    plt.figure(figsize=(8, 5))
    plt.plot(historia_energii, label='Energia całkowita')
    plt.xlabel('Iteracja')
    plt.ylabel('Energia')
    plt.title('Postęp symulowanego wyżarzania')
    plt.legend()
    plt.grid(True)
    plt.show()


atomy = pd.read_csv('atoms_positions_c60.dat', header=None, sep='\s+')
atomy.columns = ['x', 'y', 'z']

# V, _, _ = potencjal_brennera_opt(bazowy_df=atomy)
# print(V)
# pcf = korelacja_par(bazowy_df=atomy)

df_koncowy, energia_hist = symulowane_wyzarzanie_zapisywanie(bazowy_df=atomy, w_r=0.01, w_phi=0.1, w_theta=0.1, w_all=0.01)
rysuj_energie(energia_hist)



