import numpy as np
import matplotlib.pyplot as plt

filenames = {
    "1 MeV" : "build/output_h1_nd0.csv",
    "2 MeV" : "build/output_h1_nd1.csv",
    "3 MeV" : "build/output_h1_nd2.csv",
    "4 MeV" : "build/output_h1_nd3.csv",
    "5 MeV" : "build/output_h1_nd4.csv",
    "6 MeV" : "build/output_h1_nd5.csv",
    "7 MeV" : "build/output_h1_nd6.csv",
    "8 MeV" : "build/output_h1_nd7.csv",
    "9 MeV" : "build/output_h1_nd8.csv",
    "10 MeV" : "build/output_h1_nd9.csv",
    # "nPhotons->Edep" : "build/output_h1_npc.csv"
    # "Air" : "../results/air.csv",
    # "EJ-309" : "../results/ej.csv",
    # "Lead" : "../results/lead.csv",
    # "Nai" : "../results/nai.csv",
    # "Polyethylene" : "../results/polyethylene.csv",
    # "Vinyltoluene" : "../results/Vinyltoluene.csv"
}

bin_start = 0
bin_end = 150
num_bins = 300
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

plt.title('Energy deposited by neutrons')
plt.xlabel('Percentage of incident energy')
plt.ylabel('Count')
plt.yscale("log")
plt.xticks(np.arange(0, 150, 10))
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()