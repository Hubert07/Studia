import numpy as np
import matplotlib.pyplot as plt
import os
from matplotlib import cm

# Ścieżka do folderu z danymi
folder_dane = "wyniki"
folder_wykresy = "wykresy"
os.makedirs(folder_wykresy, exist_ok=True)

# Wybrane czasy do analizy
selected_times = [10, 50, 100, 200, 500, 1000, 2000, 5000] #, 60, 70, 80, 90, 100]

# Funkcja do wczytania danych z pliku
def load_data(time):
    filename = os.path.join(folder_dane, f"nptv_{time}.dat")
    data = np.loadtxt(filename)
    return {
        "time": time,
        "x": data[:, 0],
        "density": data[:, 1],
        "pressure": data[:, 2],
        "temperature": data[:, 3],
        "velocity": data[:, 4],
        "flux": data[:, 5],
    }

# Wczytaj dane
datasets = [load_data(t) for t in selected_times]

# Funkcja do rysowania i zapisywania wykresów
def plot_and_save(field, ylabel, title, filename):
    plt.figure(figsize=(10, 6))

    cmap = cm.get_cmap('plasma', len(datasets))
    for i, data in enumerate(datasets):
        color = cmap(i)
        plt.plot(data["x"], data[field], label=f't = {data["time"]}', color=color)

    plt.xlabel("x")
    plt.ylabel(ylabel)
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    filepath = os.path.join(folder_wykresy, filename)
    plt.savefig(filepath)
    plt.close()
    print(f"Zapisano wykres: {filepath}")

# Lista wielkości do analizy
quantities = [
    ("density", "Gęstość [kg/m³]", "Rozkład gęstości", "gestosc.png"),
    ("pressure", "Ciśnienie [Pa]", "Rozkład ciśnienia", "cisnienie.png"),
    ("temperature", "Temperatura [K]", "Rozkład temperatury", "temperatura.png"),
    ("velocity", "⟨√v²⟩ [m/s]", "Średnia prędkość cząstek", "predkosc.png"),
    ("flux", "Strumień jx [1/s]", "Strumień cząstek", "strumien.png"),
]

# Generowanie wykresów
for field, ylabel, title, filename in quantities:
    plot_and_save(field, ylabel, title, filename)
