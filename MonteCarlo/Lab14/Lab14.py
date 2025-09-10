import numpy as np
import matplotlib.pyplot as plt
from tqdm import tqdm

def psi_trial(r, a, c):
    return (1 + c * r) * np.exp(-a * r)

def p_density(r, a, c):
    psi = psi_trial(r, a, c)
    return r**2 * psi**2

def local_energy(r, a, c):
    numerator = -a**2 * c * r**2 + (-a**2 + 4*a*c - 2*c)*r + 2*a - 2*c - 2
    denominator = 2*c*r**2 + 2*r
    return numerator / denominator

def metropolis_mc(a, c, delta_r, N, burn_in=1000):
    r = 5.0  # initial position
    accepted = 0
    samples = []
    energies = []

    for i in range(N + burn_in):
        r_new = r + delta_r * (2 * np.random.rand() - 1)

        if r_new <= 0:
            samples.append(r)
            continue

        p_new = p_density(r_new, a, c)
        p_old = p_density(r, a, c)
        p_accept = min(p_new / p_old, 1.0)

        if np.random.rand() < p_accept:
            r = r_new
            accepted += 1

        if i >= burn_in:
            samples.append(r)
            energies.append(local_energy(r, a, c))

    return np.array(energies), np.array(samples)

def compute_energy_and_variance(a, c, delta_r=0.1, N=10**6):
    energies, _ = metropolis_mc(a, c, delta_r, N)
    mean_energy = np.mean(energies)
    std_energy = np.std(energies)
    return mean_energy, std_energy

def parameter_scan(a_range, c_range, delta_r=0.1, N=10**5):
    a_vals = np.arange(*a_range)
    c_vals = np.arange(*c_range)
    epsilon_map = np.zeros((len(a_vals), len(c_vals)))
    sigma_map = np.zeros_like(epsilon_map)

    for i, a in enumerate(tqdm(a_vals, desc="Scanning a")):
        for j, c in enumerate(c_vals):
            epsilon, sigma = compute_energy_and_variance(a, c, delta_r, N)
            epsilon_map[i, j] = epsilon
            sigma_map[i, j] = sigma

    return a_vals, c_vals, epsilon_map, sigma_map

def plot_maps(a_vals, c_vals, epsilon_map, sigma_map):
    A, C = np.meshgrid(c_vals, a_vals)

    plt.figure(figsize=(18, 5))
    
    plt.subplot(1, 3, 1)
    plt.title("Energia ε(a, c)")
    plt.contourf(C, A, epsilon_map, cmap='viridis')
    plt.xlabel('c')
    plt.ylabel('a')
    plt.colorbar()

    plt.subplot(1, 3, 2)
    plt.title("Wariancja σ(ε)")
    plt.contourf(C, A, sigma_map, cmap='plasma')
    plt.xlabel('c')
    plt.colorbar()

    plt.subplot(1, 3, 3)
    plt.title("log(σ(ε) + 1e-20)")
    plt.contourf(C, A, np.log(sigma_map + 1e-20), cmap='inferno')
    plt.xlabel('c')
    plt.colorbar()

    plt.tight_layout()
    plt.show()

def plot_histogram(samples, rmax=8, M=200, psi_exact=None, label='Simulation'):
    delta_r = rmax / M
    hist, bins = np.histogram(samples, bins=M, range=(0, rmax), density=True)
    r = 0.5 * (bins[:-1] + bins[1:])

    plt.figure(figsize=(8, 5))
    plt.plot(r, hist, label=label)

    if psi_exact:
        p_exact = r**2 * psi_exact(r)**2
        p_exact /= np.trapezoid(p_exact, r)
        plt.plot(r, p_exact, '--', label="Dokładne")

    plt.xlabel("r")
    plt.ylabel("Gęstość")
    plt.title("Histogram vs rozkład dokładny")
    plt.legend()
    plt.grid()
    plt.savefig(label)
    plt.show()

def psi_exact_100(r):
    return 2 * np.exp(-r)

def psi_exact_200(r):
    return (1 / (2 * np.sqrt(2))) * (2 - r) * np.exp(-r / 2)

# 1. Mapy
a_vals, c_vals, eps_map, sigma_map = parameter_scan(
    a_range=(0.3, 1.21, 0.02),
    c_range=(-0.7, 0.31, 0.02),
    N=10**6
)

plot_maps(a_vals, c_vals, eps_map, sigma_map)

# Dla psi 100
# _, samples = metropolis_mc(a=1.0, c=0.0, delta_r=0.1, N=10**6)
# plot_histogram(samples, psi_exact=psi_exact_100, label='Psi_100')


# Dla psi 200
N_values = [10**6, 10**7, 10**8]
labels = [r"$N=10^6$", r"$N=10^7$", r"$N=10^8$"]
colors = ['blue', 'orange', 'green']
hist_data = []
rmax = 8
M = 200
delta_r = rmax / M
bins = np.linspace(0, rmax, M + 1)
r_centers = 0.5 * (bins[:-1] + bins[1:])

# --- symulacja i histogramy ---
for N, label, color in zip(N_values, labels, colors):
    _, samples = metropolis_mc(a=0.5, c=-0.5, delta_r=0.1, N=N)
    hist, _ = np.histogram(samples, bins=bins, density=True)
    hist_data.append((r_centers, hist, label, color))

# --- dokładny rozkład ---
r_plot = np.linspace(0, rmax, 1000)
p_exact = r_plot**2 * psi_exact_200(r_plot)**2
p_exact /= np.trapz(p_exact, r_plot)  # normalizacja

# --- rysowanie ---
plt.figure(figsize=(10, 6))

for r_vals, hist, label, color in hist_data:
    plt.plot(r_vals, hist, label=label, lw=1.5, color=color)

plt.plot(r_plot, p_exact, 'k--', label='dokładny', lw=2)

plt.xlabel("r")
plt.ylabel("gęstość")
plt.title("Histogram prób dla różnych N vs rozkład dokładny")
plt.legend()
plt.grid()
plt.tight_layout()
plt.show()