import numpy as np
import matplotlib.pyplot as plt

filenames = {
    "6 MeV" : "build/output_h1_lo0.csv",
    "8 MeV" : "build/output_h1_lo1.csv",
    "10 MeV" : "build/output_h1_lo2.csv",
    "12 MeV" : "build/output_h1_lo3.csv",
    "14 MeV" : "build/output_h1_lo4.csv",
    "16 MeV" : "build/output_h1_lo5.csv",
    "18 MeV" : "build/output_h1_lo6.csv",
    "20 MeV" : "build/output_h1_lo7.csv",
    # "Energy of protons" : "build/output_h1_pe.csv",
    # "Light output" : "build/output_h1_lo.csv"
}

bin_start = 0
bin_end = 12
num_bins = 1000
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
    total_events = sum(bin_counts)
    print(total_events)
    # normalized_counts = np.array(bin_counts) / (total_events * bin_width)

    plt.hist(
        bin_edges[:-1],
        bins=bin_edges,
        weights=bin_counts,
        histtype='step',
        label=label,
        linewidth=1.5
    )

plt.title('Light output distribution by neutron incident energy')
plt.xlabel('Light output (MeVee)')
plt.ylabel('Count')
plt.yscale("log")
plt.xticks(np.arange(0, 12, 0.5))
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()