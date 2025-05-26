import numpy as np
import matplotlib.pyplot as plt

filename = 'build/output_h1_Edep.csv'

bin_counts = []
bin_edges = []
bin_start = 0
bin_end = 420
num_bins = 420

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
print("Total number of events : ", total_events, "/15000")
plt.xticks(np.arange(0, 420, 20))
plt.title('Energy deposited by neutrons')
plt.xlabel('Energy (keV)')  
plt.ylabel('Count')
# plt.yscale('log')
plt.grid(True)
plt.tight_layout()
plt.show()