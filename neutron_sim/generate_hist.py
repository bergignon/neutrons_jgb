import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

filename = 'build/output_h1_Edep.csv'

bin_counts = []
bin_edges = []
bin_start = 0
bin_end = 1500
num_bins = 1500

with open(filename, 'r') as file:
    lines = file.readlines()

data_lines = []
data_started = False
for line in lines:
    line = line.strip()
    if not data_started:
        if line.startswith('entries'):
            data_started = True
        continue
    if line:
        data_lines.append(line)


for line in data_lines[:num_bins]:  
    values = line.split(',')
    entries = float(values[0])
    bin_counts.append(entries)

bin_edges = np.linspace(bin_start, bin_end, num_bins + 1)

plt.figure(figsize=(8, 5))
plt.hist(
    bin_edges[:-1],
    bins=bin_edges,
    weights=bin_counts,
    histtype='stepfilled',
    edgecolor='black',
    color='mediumseagreen'
)

total_events = sum(bin_counts)
print("Total number of events : ", total_events, "/100000")
plt.xticks(np.arange(0, 1500, 100))
plt.title('Energy deposited by neutrons')
plt.xlabel('Energy (keV)')  
plt.ylabel('Count')
plt.yscale('log')
plt.grid(True)
plt.tight_layout()
plt.show()


############### FOR 2D HIST ###############

# filename = 'build/output_h2_Edep.csv'

# x_bins = 420
# x_min = 0
# x_max = 0.42

# y_bins = 50
# y_min = 1
# y_max = 10

# # This is necessary to include the geant4 overflow bins so the different 
# # bin numbers match
# full_x_bins = x_bins + 2
# full_y_bins = y_bins + 2

# with open(filename, 'r') as file:
#     lines = file.readlines()

# data_lines = []
# data_started = False
# for line in lines:
#     line = line.strip()
#     if not data_started:
#         if line.startswith('entries'):
#             data_started = True
#         continue
#     if line:
#         data_lines.append(line)

# if len(data_lines) != full_x_bins * full_y_bins:
#     raise ValueError(f"Expected {full_x_bins * full_y_bins} bins, got {len(data_lines)}")

# hist_full = np.zeros((full_y_bins, full_x_bins))
# for idx, line in enumerate(data_lines):
#     y_idx = idx // full_x_bins
#     x_idx = idx % full_x_bins
#     entries = float(line.split(',')[0])
#     hist_full[y_idx, x_idx] = entries

# hist_core = hist_full[1:-1, 1:-1]

# x_centers = np.linspace(x_min, x_max, x_bins)
# y_centers = np.linspace(y_min, y_max, y_bins)
# X, Y = np.meshgrid(x_centers, y_centers)

# Z = hist_core  

# fig = plt.figure(figsize=(12, 7))
# ax = fig.add_subplot(111, projection='3d')

# surf = ax.plot_surface(X, Y, Z, cmap=cm.viridis, edgecolor='k', linewidth=0.1, antialiased=True)

# ax.set_title('Energy Deposited by Neutrons')
# ax.set_xlabel('Energy deposited')
# ax.set_ylabel('Particle Energy')
# ax.set_zlabel('Count')

# plt.tight_layout()
# plt.show()