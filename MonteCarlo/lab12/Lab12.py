import os
import numpy as np
import matplotlib.pyplot as plt
import re

def load_data(file_path):
    return np.loadtxt(file_path)

def plot_position_hist2d(data, title, save_path):
    x = data[:, 0]
    y = data[:, 1]

    plt.figure(figsize=(7, 6))
    plt.hist2d(x, y, bins=100, cmap='plasma', density=True)
    plt.xlabel('x [m]')
    plt.ylabel('y [m]')
    plt.title(title)
    plt.colorbar(label='Gęstość')
    plt.axis('equal')
    plt.tight_layout()
    plt.xlim([0.9, 2.1])
    plt.ylim([-0.1, 1.1])
    plt.savefig(save_path)
    plt.close()

def plot_velocity_hist2d(data, title, save_path):
    vx = data[:, 2]
    vy = data[:, 3]

    plt.figure(figsize=(6, 5))
    plt.hist2d(vx, vy, bins=100, cmap='viridis', density=True)
    plt.xlabel('v_x [m/s]')
    plt.ylabel('v_y [m/s]')
    plt.title(title)
    plt.colorbar(label='Gęstość')
    plt.axis('equal')
    plt.tight_layout()
    plt.xlim([-1000, 1000])
    plt.ylim([-1000, 1000])
    plt.savefig(save_path)
    plt.close()

def main():
    base_path = '.'
    for folder in os.listdir(base_path):
        if re.match(r'Lab12-\d-\d{2}', folder):
            full_path = os.path.join(base_path, folder)
            start_file = os.path.join(full_path, 'rv.dat')
            end_file = os.path.join(full_path, ' rv.dat ')  # z uwzględnieniem spacji

            if os.path.isfile(start_file) and os.path.isfile(end_file):
                try:
                    initial = load_data(start_file)
                    final = load_data(end_file)

                    # Histogramy 2D położeń
                    pos2d_start = os.path.join(full_path, f"{folder}_position2d_start.png")
                    plot_position_hist2d(initial, f'{folder} – Położenie początkowe', pos2d_start)

                    pos2d_end = os.path.join(full_path, f"{folder}_position2d_end.png")
                    plot_position_hist2d(final, f'{folder} – Położenie końcowe', pos2d_end)

                    # Histogramy 2D prędkości
                    vel2d_start = os.path.join(full_path, f"{folder}_velocity2d_start.png")
                    plot_velocity_hist2d(initial, f'{folder} – Prędkość początkowa', vel2d_start)

                    vel2d_end = os.path.join(full_path, f"{folder}_velocity2d_end.png")
                    plot_velocity_hist2d(final, f'{folder} – Prędkość końcowa', vel2d_end)

                    print(f"✔ Wykresy 2D OK: {folder}")

                except Exception as e:
                    print(f"⚠ Błąd w {folder}: {e}")

if __name__ == '__main__':
    main()
