import numpy as np
import random
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

def poisson_relaxation(nx = 30, ny = 30, delta = 0.1, epsilon = 1, rho_max = 1,
                       VL = 1, VB = -1, VT = -1, tol=1e-6, max_iter=10000, omega = 1.8):
    """
    Rozwiązuje równanie Poissona ∇²V = -rho/epsilon metodą relaksacji z warunkami brzegowymi.

    Parametry:
        nx, ny: liczba punktów siatki w kierunku x i y
        delta: krok siatki (Δx = Δy)
        epsilon: przenikalność dielektryczna
        rho_max: maksymalna wartość gęstości ładunku
        sigma_rho: szerokość rozkładu gęstości
        VL, VB, VT: warunki Dirichleta na lewym, dolnym i górnym brzegu
        tol: tolerancja dla zbieżności
        max_iter: maksymalna liczba iteracji

    Zwraca:
        V: siatka potencjału o wymiarach (nx+1, ny+1)
    """

    xmax = delta * nx
    ymax = delta * ny
    sigma_rho = xmax/10

    # Współrzędne siatki
    x = np.linspace(0, xmax, nx + 1)
    y = np.linspace(0, ymax, ny + 1)
    X, Y = np.meshgrid(x, y, indexing='ij')

    # Gęstość ładunku rho(x, y)
    r_2D = (X - xmax / 2) ** 2 + (Y - ymax / 2) ** 2 # licznik argumentu e^
    rho = rho_max * np.exp(-r_2D / (2 * sigma_rho ** 2))
    # print(rho)

    # Potencjał początkowy
    V = np.zeros_like(X)

    # Warunki brzegowe Dirichleta
    V[0, :] = VL * np.sin(np.pi * y / ymax)       # lewy brzeg
    V[:, 0] = VB * np.sin(np.pi * x / xmax)       # dolny brzeg
    V[:, -1] = VT * np.sin(np.pi * x / xmax)      # górny brzeg

    # Relaksacja
    for iteration in range(max_iter):
        V_old = V.copy()

        # Iteracja wewnętrzna
        for i in range(1, nx):
            for j in range(1, ny):
                ## Warunek relaksacji
                if np.isnan(V[i, j]):
                    print(f"NaN detected at V[{i},{j}] in iteration {iteration}")
                    break
                V[i, j] = (1-omega)*V_old[i, j] + 0.25 * omega * (V_old[i+1, j] + V_old[i-1, j] + V_old[i, j+1] + V_old[i, j-1] + delta**2 * rho[i, j] / epsilon)
                
                ## Działająca wersja
#                V[i, j] = 0.25 * (V_old[i+1, j] + V_old[i-1, j] + V_old[i, j+1] + V_old[i, j-1] + delta**2 * rho[i, j] / epsilon)

        # Warunek Neumanna (prawy brzeg): dV/dx = 0 → V[nx, j] = V[nx-1, j]
        V[nx, 1:ny] = V[nx-1, 1:ny]

        # Sprawdź zbieżność (w metryce L_max)
        diff = np.max(np.abs(V - V_old))
        if diff < tol:
            print(f"Zbieżność osiągnięta po {iteration} iteracjach (ΔV = {diff:.2e})")
            break
    else:
        print("Osiągnięto maksymalną liczbę iteracji bez zbieżności.")

    return V


def plot_potential(V, delta = 0.1, title="Potencjał V(x, y)", label = 'Potencjał V'):
    """
    Rysuje rozkład potencjału V(x, y) jako mapę kolorów.

    Parametry:
        V: 2D tablica potencjału (rozmiar [nx+1, ny+1])
        delta: krok siatki (Δx = Δy)
        title: tytuł wykresu
    """
    nx, ny = V.shape[0] - 1, V.shape[1] - 1
    xmax = nx * delta
    ymax = ny * delta

    x = np.linspace(0, xmax, nx + 1)
    y = np.linspace(0, ymax, ny + 1)

    plt.figure(figsize=(8, 6))
    cp = plt.contourf(x, y, V.T, levels=50, cmap='viridis')  # Uwaga: V.T = transpozycja, bo matplotlib
    plt.colorbar(cp, label=label)
    plt.title(title)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.axis("equal")
    plt.tight_layout()
    plt.savefig(title + '.png')
    # plt.show()
    plt.clf()
    plt.close()

def monte_carlo_grid(nx = 30, ny = 30, delta = 0.1, epsilon = 1, rho_max = 1,
                     VL = 1, VB = -1, VT = -1, Nchains=100, nlength=100, B_ij=0):
    """
    Oblicza potencjał V oraz jego odchylenie standardowe metodą Monte Carlo
    na siatce (nx+1)x(ny+1) z warunkami brzegowymi Dirichleta i Neumanna.
    """

    # Inicjalizacja siatki
    V = np.zeros((nx + 1, ny + 1))
    sigmaV = np.zeros_like(V)
    S = np.zeros_like(V, dtype=int)
    B = np.zeros_like(V, dtype=int)

    xmax = delta * nx
    ymax = delta * ny
    sigma_rho = xmax/10

    # Gęstość ładunku
    rho = np.zeros_like(V)
    for i in range(nx + 1):
        for j in range(ny + 1):
            x = i * delta
            y = j * delta
            rho[i, j] = rho_max * np.exp(
                -((x - xmax) ** 2 + (y - ymax) ** 2) / (2 * sigma_rho ** 2)
            )

    # Warunki brzegowe Dirichleta
    for j in range(ny + 1):
        y = j * delta
        V[0, j] = VL * np.sin(np.pi * y / ymax)
        B[0, j] = 1

    for i in range(nx + 1):
        x = i * delta
        V[i, 0] = VB * np.sin(np.pi * x / xmax)
        V[i, ny] = VT * np.sin(np.pi * x / xmax)
        B[i, 0] = 1
        B[i, ny] = 1

    # Pętla po wszystkich węzłach wewnętrznych
    for i0 in range(1, nx):
        for j0 in range(1, ny):
            sumV1 = 0.0
            sumV2 = 0.0
            kchains = 0

            for _ in range(Nchains):
                i, j = i0, j0
                g = 0.0

                for _ in range(nlength):
                    m = random.randint(0, 3)
                    if m == 0:
                        i -= 1
                    elif m == 1:
                        i += 1
                    elif m == 2:
                        j -= 1
                    elif m == 3:
                        j += 1

                    # Odbicie od prawego brzegu (warunek Neumanna)
                    if i == nx + 1:
                        i = nx - 1

                    # Absorpcja na brzegu Dirichleta
                    if B[i, j] == 1:
                        dV = V[i, j] + g
                        sumV1 += dV
                        sumV2 += dV ** 2
                        kchains += 1
                        break

                    # Wkład od gęstości
                    g += (delta ** 2) * rho[i, j] / (4 * epsilon)

            if kchains > 0:
                V1 = sumV1 / kchains
                V2 = sumV2 / kchains
                V[i0, j0] = V1
                sigmaV[i0, j0] = np.sqrt((V2 - V1 ** 2) / kchains)
                B[i0, j0] = B_ij  # aktualizacja maski B
                S[i0, j0] = kchains
            else:
                V[i0, j0] = 0
                sigmaV[i0, j0] = 0
                S[i0, j0] = 0

    V1 = sumV1 / kchains
    V2 = sumV2 / kchains

    return V, sigmaV, B, S, V1, V2


V_rel = poisson_relaxation(max_iter=10000, omega = 1)
plot_potential(V_rel, title='Potencjał V(x, y) metodą relaksacji')

V_MC, sigma_V_MC, B_MC, S_MC, V1, V2 = monte_carlo_grid(Nchains=300, nlength=300, B_ij = 1)
plot_potential(V_MC, title='Potencjał V(x, y) metodą Monte Carlo')
plot_potential(sigma_V_MC, title='Rozkład błędu')
plot_potential(S_MC, title='Zaabsorbowane łańcuchy', label = 'Liczba zaabsorbowanych łańcuchów')
plot_potential(np.abs(V_rel-V_MC), title='Różnica potencjałów |V_MC - V_REL|')
