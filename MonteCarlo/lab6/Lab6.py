import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.stats import norm
import matplotlib.patches as patches

def symulacja_otwarty(Nmax=10**2, N=1001, dt=0.1, D=1):
    mi = 0
    sigma = np.sqrt(2*D*dt)

    X = np.zeros([Nmax, N])
    Y = np.zeros([Nmax, N])
    for n in range(Nmax-1):
        for t in range(1, N):
            # i iteruje od 1 do N -> N iteracji + zainicjalizowane 0
            dX, dY = norm.rvs(mi, sigma, size=2)
            X[n, t] = X[n, t-1] + dX
            Y[n, t] = Y[n, t-1] + dY
    return X, Y

def symulacja_zamknięty(Nmax=10**2, N=1001, dt=0.1, D=1, omega=10):
    mi = 0
    sigma = np.sqrt(2*D*dt)

    X = np.zeros([Nmax, N])
    Y = np.zeros([Nmax, N])
    theta = np.zeros([Nmax, N])

    for n in range(Nmax-1):
        for t in range(1, N):
            # i iteruje od 1 do N -> N iteracji + zainicjalizowane 0
            dX, dY = norm.rvs(mi, sigma, size=2)
            X[n, t] = X[n, t-1] + dX
            Y[n, t] = Y[n, t-1] + dY
    return X, Y

def wspolczynnik_dyfuzji_w_czasie (X=np.zeros([10, 20]), Y=np.zeros([10, 20])):
    """
    D_xx, D_xy, D_yy
    """

    N = X.shape[0]
    T = X.shape[1]
    #print(N, T)
    X_est = np.zeros(T)
    Y_est = np.zeros(T)
    XY_est = np.zeros(T)
    XX_est = np.zeros(T)
    YY_est = np.zeros(T)
    D_xx = np.zeros(T)
    D_yy = np.zeros(T)
    D_xy = np.zeros(T)

    for t in range(T):
        X_est[t] = (1/N) * np.sum(X[:, t])
        Y_est[t] = (1/N) * np.sum(Y[:, t])
        XY_est[t] = (1/N) * np.sum(X[:, t]*Y[:, t])
        XX_est[t] = (1/N) * np.sum(X[:, t]**2)
        YY_est[t] = (1/N) * np.sum(Y[:, t]**2)

        D_xx[t] = (XX_est[t] - X_est[t]**2)/(2*(t+1)*dt) 
        D_yy[t] = (YY_est[t] - Y_est[t]**2)/(2*(t+1)*dt) 
        D_xy[t] = (XY_est[t] - X_est[t]*Y_est[t])/(2*(t+1)*dt) 

    return pd.DataFrame(np.array([D_xx, D_xy, D_yy]).T, columns=['D_xx', 'D_xy', 'D_yy'])


def wspolczynnik_dyfuzji_podsumowanie (X=np.zeros([10, 20]), Y=np.zeros([10, 20])):
    """
    D1_XX_est, D1_XY_est, D1_YY_est, SD_XX_est, SD_XY_est, SD_YY_est
    """
    N = X.shape[0]
    T = X.shape[1]
    wspolczynniki = wspolczynnik_dyfuzji_w_czasie(X, Y)
    D_xx, D_xy, D_yy = wspolczynniki['D_xx'].values, wspolczynniki['D_xy'].values, wspolczynniki['D_yy'].values
    
    D1_XX_est = (1/T) * np.sum(D_xx)
    D2_XX_est = (1/T) * np.sum(D_xx**2)
    SD_XX_est = np.sqrt((D2_XX_est - D1_XX_est**2)/T)

    D1_XY_est = (1/T) * np.sum(D_xy)
    D2_XY_est = (1/T) * np.sum(D_xy**2)
    SD_XY_est = np.sqrt((D2_XY_est - D1_XY_est**2)/T)

    D1_YY_est = (1/T) * np.sum(D_yy)
    D2_YY_est = (1/T) * np.sum(D_yy**2)
    SD_YY_est = np.sqrt((D2_YY_est - D1_YY_est**2)/T)

    return np.array([D1_XX_est, D1_XY_est, D1_YY_est, SD_XX_est, SD_XY_est, SD_YY_est])

# Parametry 
D = 1
Nmax = 10**3
dt = 0.1
tmax = 100
# Liczba kroków:
N = int(tmax / dt + 1)

## Układ otwarty

# df = pd.DataFrame()
# for Nmax in [10**2, 10**3, 10**4, 10**5]:
#     X, Y = symulacja_otwarty(Nmax, N, dt, D)
#     data = wspolczynnik_dyfuzji_w_czasie(X, Y)
#     data['Nmax'] = Nmax
#     df = pd.concat([data, df])

# df['X'] = df.index * 0.2
# df_long = pd.melt(df, 
#                   id_vars=['X', 'Nmax'], 
#                   value_vars=['D_xx', 'D_xy', 'D_yy'], 
#                   var_name='Type', 
#                   value_name='Value')

# # Otwarty w czasie

# max_val = 1.1*max(abs(X).max(), abs(Y).max())
# plt.scatter(X[:, -1], Y[:, -1], color='black', alpha=0.3, label='Tmax')
# plt.scatter(X[:, int(N/2)], Y[:, int(N/2)], color='blue', alpha=0.3, label='T1/2')
# plt.scatter(X[:, int(N/10)], Y[:, int(N/10)], color='red', alpha=0.3, label='T0.1')

# plt.xlim(-max_val, max_val)
# plt.ylim(-max_val, max_val)
# plt.axhline(0, color='gray', linewidth=1)
# plt.axvline(0, color='gray', linewidth=1)
# plt.title('Proces dyfuzji w czasie')
# plt.xlabel('X')
# plt.ylabel('Y')
# plt.grid(True)
# plt.gca().set_aspect('equal', adjustable='box')
# plt.legend()
# plt.savefig('Dyfuzja_otwarty.png')
# plt.clf()
# plt.close()

# # Faceted
# g = sns.relplot(
#     data=df_long,
#     kind='line',
#     x='X',
#     y='Value',
#     hue='Type',
#     col='Nmax',
#     col_wrap=1,
#     facet_kws={'sharey': True, 'sharex': True},
#     height=4,
#     aspect=1.2
# )

# g.set_titles('Nmax = {col_name}')
# g.set_axis_labels('t', 'D')
# g.tight_layout()
# plt.savefig('Dyfuzja_otwarty_liniowy.png')
# plt.clf()
# plt.close()

## Układ zamknięty
D = 1
Nmax = 10**5
dt = 0.1
tmax = 1000
# Liczba kroków:
N = int(tmax / dt + 1)
omega = [10, 50, 100]

# Okręgi
R = np.array([0, 0])
rR = 5
A = np.array([3, 0])
rA = 0.1
S = np.array([-4.5, 0])

df = pd.DataFrame()

def przejscie(P, dP, sA, rA):
    f = P - sA

    a = np.dot(dP, dP)
    b = 2 * np.dot(f, dP)
    c = np.dot(f, f) - rA**2
    delta = b**2 - 4*a*c

    if delta < 0:
        return False
    else:
        delta = np.sqrt(delta)
        t1 = (-b - delta) / (2*a)
        t2 = (-b + delta) / (2*a)
        if (0 <= t1 <= 1) or (0 <= t2 <= 1):
            return True

    return False


def przesun_z_odbiciem(P, dP, rR, rek=0, max_rek=5):
    if rek > max_rek:
        assert np.linalg.norm(P) <= rR + 1e-8, f"Ucieczka: rekurencja"
        # Utknęło w ścianie - rekurencyjne przerwanie
        return P
    
    a = np.dot(dP, dP)
    b = 2 * np.dot(dP, P)
    c = np.dot(P, P) - rR**2
    delta = b**2 - 4 * a * c
    if delta < 0:
        assert np.linalg.norm(P+dP) <= rR + 1e-8, f"Ucieczka: ujemna delta!"
        return P + dP
    else:
        # Wyszłaby na zewnątrz
        ## do while -> rekursywne wywołanie
        sqrt_d = np.sqrt(delta)
        t1 = (-b - sqrt_d) / (2 * a)
        t2 = (-b + sqrt_d) / (2 * a)

        if [t for t in [t1, t2] if 1e-10 < t < 1 - 1e-10]:
            t_hit = min(t for t in [t1, t2] if 1e-10 < t < 1 - 1e-10)
            P_hit = P + t_hit * dP
            N = (P_hit) / np.linalg.norm(P_hit)
            dP_ref = dP - 2 * np.dot(dP, N) * N 
            dP_ref = dP_ref / np.linalg.norm(dP_ref) * (1 - t_hit) * np.linalg.norm(dP)

            if np.allclose(P, P_hit, atol=1e-8):
                # Utknęło w ścianie - zblżeniowe przerwanie
                return P
            
            return przesun_z_odbiciem(P_hit, dP_ref, rR, rek+1)
        else:
            # Zostaje w środku 
            if np.linalg.norm(P+dP) <= rR - 1e-8:
                return P + dP
            else:
                return P

def symulacja_zamknięty(Nmax=10**2, N=1001, dt=0.1, D=1, omega=10, R=np.array([0, 0]), rR=5, S=np.array([-4.5, 0]), sA=np.array([3, 0]), rA=0.1):
    """
    return: X, Y, theta
    """
    mi = 0
    sigma = np.sqrt(2*D*dt)

    X = np.zeros([Nmax, N]) + S[0]
    Y = np.zeros([Nmax, N]) + S[1]
    theta = np.zeros([Nmax, N])
    zanikanie = np.zeros(N)

    for t in range(1, N):
        if (t)*omega <= Nmax:
            theta[(t-1)*omega:(t)*omega, t:] = 1

        for n in range(Nmax-1):
            # Jeżeli jest aktywna
            if theta[n, t] == 1:
                dX, dY = norm.rvs(mi, sigma, size=2)
                P = np.array([X[n, t-1], Y[n, t-1]])
                dP = np.array([dX, dY])
                if przejscie(P, dP, sA, rA):
                    # Pochłąniecie
                    theta[n, t:] = 0
                    zanikanie[t] += 1
                elif np.linalg.norm(P+dP) <= rR:
                    # Zostaje w środku - przypadek 1
                    X[n, t] = X[n, t-1] + dX
                    Y[n, t] = Y[n, t-1] + dY
                else:
                    final_point = przesun_z_odbiciem(P, dP, rR, 0)
                    assert np.linalg.norm(final_point) <= rR + 1e-8, f"Ucieczka: po odbiciu"
                    X[n, t] = final_point[0]
                    Y[n, t] = final_point[1]
                        
    return X, Y, theta, zanikanie

def ciecie_w_czase(X, Y, theta, t0=0):
    mask = theta[:, t0] == 1
    return X[mask, t0], Y[mask, t0]

X, Y, theta, zanikanie = symulacja_zamknięty(Nmax=Nmax, N=N, dt=dt, D=D, omega=10, S=np.array([-4.5, 0]), rA=0.5)

ewolucja_w_czasie = pd.DataFrame(np.sum(theta, axis=0), columns=['Aktywne cząstki'])
ewolucja_w_czasie['t'] = ewolucja_w_czasie.index * dt
# Create the plot
plt.plot(ewolucja_w_czasie['t'], ewolucja_w_czasie['Aktywne cząstki'], label='Aktywne cząstki')
plt.xlabel('t')
plt.ylabel('Liczba cząstek')
plt.title('Aktywne cząstki w czasie')
plt.grid(True)
plt.legend()
plt.savefig('Ewolucja w czasie.png')
plt.clf()
plt.close()
#print(ewolucja_w_czasie)
#print(zanikanie)

max_val = 1.1*max(abs(X).max(), abs(Y).max())
X0, Y0 = ciecie_w_czase(X, Y, theta, t0=1)
X1, Y1 = ciecie_w_czase(X, Y, theta, t0=10)
X2, Y2 = ciecie_w_czase(X, Y, theta, t0=100)
X3, Y3 = ciecie_w_czase(X, Y, theta, t0=1000)
Xi = [X0, X1, X2, X3]
Yi = [Y0, Y1, Y2, Y3]
Li = [0.1, 1, 10, 100]

fig, axs = plt.subplots(2, 2, figsize=(12, 12))
axs = axs.flatten()
for i, ax in enumerate(axs):
    ax.scatter(Xi[i], Yi[i], color='red', alpha=0.3, label='t={}'.format(Li[i]), marker='.')
    ax.scatter(S[0], S[1], color='yellow', s=20, label='Źródło omega={}'.format(10), edgecolors='black', zorder=3)
    ax.scatter(A[0], A[1], color='black', s=40, label='Absorber rA={}'.format(rA), edgecolors='black', zorder=3)

    circle = patches.Circle(R, rR, fill=False, edgecolor='blue', linewidth=1.5, linestyle='--', label=f'Okrąg, r={rR}')
    ax.add_patch(circle)

    ax.set_xlim(-max_val, max_val)
    ax.set_ylim(-max_val, max_val)
    ax.axhline(0, color='gray', linewidth=1)
    ax.axvline(0, color='gray', linewidth=1)
    ax.set_title(f'Proces dyfuzji - t={Li[i]}')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.grid(True)
    ax.set_aspect('equal', adjustable='box')

handles, labels = axs[0].get_legend_handles_labels()
fig.legend(handles, labels, loc='upper center', ncol=4)
plt.tight_layout(rect=[0, 0, 1, 0.95])
plt.savefig('Dyfuzja_zamknięty.png')
plt.clf()
plt.close()
