import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
import numpy as np
import pandas as pd
from matplotlib.colors import LinearSegmentedColormap

# Parametry skalowania (jak wcześniej)
dx = 0.002
dy = 0.0006
x_detect = 0.150
dx_detect = 0.010
x_tol = dx_detect / 2
y_tol = 1e-5

# Definicja koloru: czarny -> żółty
colors = [(0, 0, 0), (1, 1, 0)]  # RGB czarny -> żółty
cmap_bw_yellow = LinearSegmentedColormap.from_list("bw_yellow", colors)

# Wczytanie i rozdzielenie trajektorii

title = 'Trajektorie (warunki 3.1)'
with open("all_paths.dat") as f:

# title = 'Wykryte wiązki (warunki 3.1)'
# with open("source_detection_paths.dat") as f:

    content = f.read()
trajectories_raw = content.strip().split('\n\n')

fig, ax = plt.subplots(figsize=(10, 6))
ax.set_facecolor('black')  # czarne tło

for traj in trajectories_raw:
    from io import StringIO
    df = pd.read_csv(StringIO(traj), delim_whitespace=True, header=None, names=['x', 'y', 'intensity'])
    print(df)
    # Filtruj trajektorie kończące się w (x_detect, y=0)
    x_end, y_end = df.iloc[-1]['x'], df.iloc[-1]['y']
    if abs(x_end - x_detect) <= x_tol and abs(y_end) <= y_tol:
        continue

    # Przeskaluj
    df['x'] = df['x'] / dx
    df['y'] = df['y'] / dy

    points = np.array([df['x'], df['y']]).T.reshape(-1, 1, 2)
    segments = np.concatenate([points[:-1], points[1:]], axis=1)
    intensities = df['intensity'].rolling(2).mean().dropna().values

    lc = LineCollection(segments, cmap=cmap_bw_yellow, norm=plt.Normalize(0, 1))
    lc.set_array(intensities)
    lc.set_linewidth(2)
    ax.add_collection(lc)


ax.set_xlabel('x / dx')
ax.set_ylabel('y / dy')

ax.set_title(title)
ax.autoscale()
ax.set_xlim([0, 100])
ax.grid(False)  # opcjonalnie wyłącz grid dla lepszego efektu na czarnym tle

cbar = plt.colorbar(lc, ax=ax)
cbar.set_label('Intensywność')

plt.savefig(title+'.png')
plt.tight_layout()
plt.show()
