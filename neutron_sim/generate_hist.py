import numpy as np
import matplotlib.pyplot as plt

filenames = {
    # "EJ-309":'output/g662edep-ej-270-700.csv',
    # 'Pb': 'output/g662edep-pb70-700.csv',
    # 'NaI': 'output/g662edep-nai70-700.csv'
    "EJ-NEUTRON" : "output/output_h1_neutronD.csv"
}

bin_start = 0
bin_end = 700
num_bins = 70
bin_edges = np.linspace(bin_start, bin_end, num_bins + 1)

# Plot configuration
plt.figure(figsize=(10, 6))

# Loop through each file and plot its histogram
for label, filename in filenames.items():
    bin_counts = []
    
    with open(filename, 'r') as file:
        lines = file.readlines()

    # Skip header lines and start after "entries"
    data_started = False
    for line in lines:
        line = line.strip()
        if not data_started:
            if line.startswith('entries'):
                data_started = True
            continue
        if line:
            values = line.split(',')
            entries = float(values[0])
            bin_counts.append(entries)

    bin_counts = bin_counts[:num_bins]

    # Normalize if needed:
    # bin_width = bin_edges[1] - bin_edges[0]
    # total_events = sum(bin_counts)
    # normalized_counts = np.array(bin_counts) / (total_events * bin_width)

    plt.hist(
        bin_edges[:-1],
        bins=bin_edges,
        weights=bin_counts,
        histtype='step',
        label=label,
        linewidth=1.5
    )

plt.title('Energy Deposited by Gammas')
plt.xlabel('Energy (keV)')
plt.ylabel('Counts')
# plt.yscale("log")
plt.xticks(np.arange(0, 701, 50))
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()