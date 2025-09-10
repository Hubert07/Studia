import numpy as np

# Wczytaj absorption.dat jako tablicę 2D
absorption = np.loadtxt("absorption.dat")

# Wczytaj reflectance i transmittance jako tablice 1D
reflectance = np.loadtxt("reflectance.dat")
transmittance = np.loadtxt("transmittance.dat")

# Skumulowane wartości (całkowite sumy)
total_absorption = np.sum(absorption)
total_reflectance = np.sum(reflectance)
total_transmittance = np.sum(transmittance)

# Wyświetlenie wyników
print(f"Całkowita absorpcja:      {total_absorption:.6f}")
print(f"Całkowita reflektancja:   {total_reflectance:.6f}")
print(f"Całkowita transmitancja:  {total_transmittance:.6f}")

# Suma całkowita (dla sprawdzenia zachowania energii)
total_energy = total_absorption + total_reflectance + total_transmittance
print(f"Suma całkowita energii:   {total_energy:.6f}")

import matplotlib.pyplot as plt

plt.imshow(absorption, origin='lower', cmap='inferno')
plt.colorbar(label="Absorpcja")
plt.title("Rozkład absorpcji")
plt.show()
