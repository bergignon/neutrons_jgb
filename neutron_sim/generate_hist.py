import numpy as np
import matplotlib.pyplot as plt

# Read and parse the file
filename = 'build/output_h1_Edep.csv'

bin_counts = []
bin_edges = []
bin_start = 0
bin_end = 450
num_bins = 225

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

# Extract bin contents
for line in data_lines[:num_bins]:  # Only take the number of bins
    values = line.split(',')
    entries = float(values[0])
    bin_counts.append(entries)

# Bin edges
bin_edges = np.linspace(bin_start, bin_end, num_bins + 1)

# Plotting
plt.figure(figsize=(8, 5))
plt.hist(
    bin_edges[:-1],
    bins=bin_edges,
    weights=bin_counts,
    histtype='stepfilled',
    edgecolor='black',
    color='mediumseagreen'
)

plt.xticks(np.arange(0, 451, 20))
plt.title('Energy deposited by neutrons')
plt.xlabel('Energy (keV)')  
plt.ylabel('Count')
plt.yscale('log')
plt.grid(True)
plt.tight_layout()
plt.show()